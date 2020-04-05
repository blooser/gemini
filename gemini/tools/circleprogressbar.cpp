#include "circleprogressbar.h"

#include <QPainter>
#include <QPainterPath>

#include <QtMath>

Q_LOGGING_CATEGORY(circleProgressBar, "circle.progressbar")

namespace {
    constexpr int CIRCLE_ANGLE = 360;
    constexpr int LINE_WIDTH = 8;
}

CircleProgressBar::CircleProgressBar(QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_from(0),
      m_to(100),
      m_value(0)
{
    setFlag(QQuickItem::ItemHasContents);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    setupConnections();
}

int CircleProgressBar::visualValue() const {
    return m_visualValue;
}

qreal CircleProgressBar::progressAngle() const {
    if (m_value < 0) {
        return 0;
    }

    return ((static_cast<qreal>(m_value)/m_to) * CIRCLE_ANGLE);
}

QPen CircleProgressBar::pen(const QColor color) {
    QPen pathPen;
    pathPen.setWidth(LINE_WIDTH);
    pathPen.setColor(color);
    pathPen.setCapStyle(Qt::RoundCap);
    return pathPen;
}

void CircleProgressBar::paint(QPainter *painter) {
    if (!painter) {
        qCWarning(circleProgressBar) << "Painter is empty!";
        return;
    }

    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(4, 4);

    QPainterPath path;
    path.moveTo(width()/2, 0);
    path.arcTo(QRectF(0, 0, width() - LINE_WIDTH, height() - LINE_WIDTH), 90, -CIRCLE_ANGLE);

    painter->strokePath(path, pen(m_backgroundColor));

    if (progressAngle() > 0) {
        QPainterPath progressPath;
        progressPath.moveTo(width()/2, 0);
        progressPath.arcTo(QRectF(0, 0, width() - LINE_WIDTH, height() - LINE_WIDTH), 90, -progressAngle());

        painter->strokePath(progressPath, pen(m_progressbarColor));
    }
}

bool CircleProgressBar::contains(const QPointF &point) const {
    QPointF center(width()/2, height()/2);
    QPointF distance = point - center;

    // Check the point is on the circle line
    return qSqrt(distance.x() * distance.x() + distance.y() * distance.y()) < width()/2 and
           qSqrt(distance.x() * distance.x() + distance.y() * distance.y()) > (width()/2 - LINE_WIDTH);
}

qreal CircleProgressBar::pointToAngle(const QPointF &point) {
    QPointF center(width()/2, height()/2);
    QPointF distance = point - center;
    qreal theta = qAtan2(distance.y(), distance.x()) * 180.0/M_PI + 90/** Shift to top **/;
    return (theta < 0) ? 360 + theta : theta;
}

qreal CircleProgressBar::angleToValue(qreal angle) {
    return m_to * angle / CIRCLE_ANGLE;
}

void CircleProgressBar::mousePressEvent(QMouseEvent *event) {
    if (not event) {
        return;
    }

    emit changeValue(angleToValue(pointToAngle(event->pos())));
}

void CircleProgressBar::hoverEnterEvent(QHoverEvent *event) {
    if (not event) {
        return;
    }

    m_containsMouse = true;
    emit containsMouseChanged(m_containsMouse);
}

void CircleProgressBar::hoverMoveEvent(QHoverEvent *event) {
    if (not event) {
        return;
    }

    m_mouse = event->pos();
    emit mouseChanged(m_mouse);

    m_visualValue = angleToValue(pointToAngle(m_mouse));
    emit visualValueChanged(m_visualValue);
}

void CircleProgressBar::hoverLeaveEvent(QHoverEvent *event) {
    if (not event) {
        return;
    }

    m_containsMouse = false;
    emit containsMouseChanged(m_containsMouse);
}

bool CircleProgressBar::containsMouse() const {
    return m_containsMouse;
}

QPoint CircleProgressBar::mouse() const {
    return m_mouse;
}

void CircleProgressBar::setupConnections() {
    auto redraw = [&]() { update(); };

    connect(this, &CircleProgressBar::fromChanged, this, redraw);
    connect(this, &CircleProgressBar::valueChanged, this, redraw);
    connect(this, &CircleProgressBar::toChanged, this, redraw);
}
