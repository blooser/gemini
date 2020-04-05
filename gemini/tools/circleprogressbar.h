#ifndef CIRCLEPROGRESSBAR_H
#define CIRCLEPROGRESSBAR_H

#include <QQuickPaintedItem>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(circleProgressBar)

class CircleProgressBar : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(int from MEMBER m_from NOTIFY fromChanged)
    Q_PROPERTY(int to MEMBER m_to NOTIFY toChanged)
    Q_PROPERTY(int value MEMBER m_value NOTIFY valueChanged)
    Q_PROPERTY(int visualValue READ visualValue NOTIFY visualValueChanged)
    Q_PROPERTY(QColor backgroundColor MEMBER m_backgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor progressbarColor MEMBER m_progressbarColor NOTIFY progressbarColorChanged)
    Q_PROPERTY(bool containsMouse READ containsMouse NOTIFY containsMouseChanged)
    Q_PROPERTY(QPoint mouse READ mouse NOTIFY mouseChanged)

public:
    CircleProgressBar(QQuickItem *parent=nullptr);

    void paint(QPainter *painter) override;
    bool contains(const QPointF &point) const override;

    int visualValue() const;

    bool containsMouse() const;
    QPoint mouse() const;

signals:
    void fromChanged(int from);
    void toChanged(int to);
    void valueChanged(int value);
    void visualValueChanged(const int visualValue);
    void backgroundColorChanged(const QColor &color);
    void progressbarColorChanged(const QColor &color);
    void containsMouseChanged(const bool containsMouse);
    void mouseChanged(const QPoint &mouse);

    // Set new value
    void changeValue(const qreal &newValue);

protected:
    // Visual calculations
    qreal pointToAngle(const QPointF &point);
    qreal angleToValue(qreal angle);

    // Mouse
    void mousePressEvent(QMouseEvent *event) override;

    // Hover
    void hoverEnterEvent(QHoverEvent *event) override;;
    void hoverMoveEvent(QHoverEvent *event) override;
    void hoverLeaveEvent(QHoverEvent *event) override;

private:
    int m_from;
    int m_to;
    int m_value;
    int m_visualValue;

    bool m_containsMouse;
    QPoint m_mouse;

    QColor m_backgroundColor;
    QColor m_progressbarColor;

    qreal progressAngle() const;
    QPen pen(const QColor color);

    void setupConnections();
};

#endif // CIRCLEPROGRESSBAR_H
