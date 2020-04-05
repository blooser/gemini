#include "picker.h"

#include <QRandomGenerator>

Q_LOGGING_CATEGORY(picker, "picker")

Picker::Picker(QObject *parent)
    : QObject(parent),
      m_model(nullptr),
      m_modelSize(0),
      m_running(false),
      m_interval(5000) {

    setTimerInterval(m_interval);
    setupConnections();
}

bool Picker::running() const {
    return m_running;
}

int Picker::interval() const {
    return m_interval;
}

QString Picker::roleName() const {
    return m_roleName;
}

QAbstractItemModel* Picker::model() const {
    return m_model;
}

QVariant Picker::data() const {
    return m_data;
}

int Picker::modelSize() const {
    return m_modelSize;
}

void Picker::setRunning(const bool running) {
    if (m_running == running) {
        return;
    }

    m_running = running;
    emit runningChanged(m_running);
}

void Picker::setInterval(const int interval) {
    if (m_interval == interval) {
        return;
    }

    m_interval = interval;
    emit intervalChanged(m_interval);
}

void Picker::setModel(QAbstractItemModel *model) {
    m_model = model;
    m_modelSize = m_model->rowCount();
    emit modelChanged(m_model);

    update();
}

void Picker::setRoleName(const QString &roleName) {
    if (m_roleName == roleName) {
        return;
    }

    m_roleName = roleName;
    emit roleNameChanged(m_roleName);
}

void Picker::setTimerInterval(const int interval) {
    m_timer.setInterval(interval);
}

void Picker::toggleTimer(const bool running) {
    if (running) {
        m_timer.start();
    } else {
        m_timer.stop();
    }
}

void Picker::pick() {
    if (!m_model) {
        qCWarning(picker) << "There is no model selected!";
        return;
    }

    if (m_modelSize == 0) {
        qCWarning(picker) << "Model is empty!";
        return;
    }

    int random = QRandomGenerator::system()->bounded(m_modelSize);
    int role = m_model->roleNames().key(m_roleName.toUtf8());

    auto index = m_model->index(random, 0);
    m_data = m_model->data(index, role);

    emit picked(m_data);
}

void Picker::observe() {
    connect(m_model, &QAbstractItemModel::modelReset,
            this, &Picker::update);
    connect(m_model, &QAbstractItemModel::rowsInserted,
            this, &Picker::update);
    connect(m_model, &QAbstractItemModel::rowsRemoved,
            this, &Picker::update);
}

void Picker::update() {
    m_modelSize = m_model->rowCount();
    emit modelSizeChanged(m_modelSize);
}

void Picker::setupConnections() {
    connect(this, &Picker::runningChanged,
            this, &Picker::toggleTimer);
    connect(this, &Picker::intervalChanged,
            this, &Picker::setTimerInterval);
    connect(this, &Picker::modelChanged,
            this, &Picker::observe);
    connect(&m_timer, &QTimer::timeout,
            this, &Picker::pick);
}

void Picker::classBegin() {

}

void Picker::componentComplete() {
    if (m_model and m_modelSize > 0) {
        pick();
    }
}
