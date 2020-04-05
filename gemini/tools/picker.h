#ifndef PICKER_H
#define PICKER_H

#include <QObject>
#include <QAbstractItemModel>
#include <QQmlParserStatus>
#include <QTimer>
#include <QVariant>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(picker)

class Picker : public QObject,
               public QQmlParserStatus {
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(bool running READ running
               WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(int interval READ interval
               WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(QAbstractItemModel* model READ model
               WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(int modelSize READ modelSize
               NOTIFY modelSizeChanged)
    Q_PROPERTY(QString roleName READ roleName
               WRITE setRoleName NOTIFY roleNameChanged)
    Q_PROPERTY(QVariant data READ data
               NOTIFY picked)

public:
    explicit Picker(QObject *parent = nullptr);

    // QQmlParserStatus
    void classBegin() override;
    void componentComplete() override;

    bool running() const;
    void setRunning(const bool running);

    int interval() const;
    void setInterval(const int interval);

    QAbstractItemModel* model() const;
    void setModel(QAbstractItemModel *model);

    QString roleName() const;
    void setRoleName(const QString &roleName);

    int modelSize() const;
    QVariant data() const;

private slots:
    void toggleTimer(const bool running);
    void setTimerInterval(const int interval);
    void pick();
    void observe();
    void update();

signals:
    void runningChanged(const bool running);
    void intervalChanged(int interval);
    void modelChanged(const QAbstractItemModel *model);
    void modelSizeChanged(const int modelSize);
    void roleNameChanged(const QString &roleName);
    void picked(const QVariant &data);

private:
    QAbstractItemModel* m_model;
    int m_modelSize;
    QString m_roleName;
    QTimer m_timer;
    QVariant m_data;
    bool m_running;
    int m_interval;

    void setupConnections();
};

#endif // PICKER_H
