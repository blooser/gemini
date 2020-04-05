#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include "../common/enums.h"
#include "../processes/processexecutor.h"
#include "../data/playlistdata.h"
#include "../models/proxy/readmodel.h"
#include "../models/proxy/songsinrelations.h"

#include <memory>

#include "modelcontroller.h"
#include "filescontroller.h"
#include "databasecontroller.h"

#include <QThread>
#include <QVector>
#include <QMap>
#include <QIdentityProxyModel>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(dataController)

class Process;

class DataController : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool processing READ processing NOTIFY processingChanged)

public:
    explicit DataController(QObject *parent = nullptr);
    explicit DataController(const QString &corePath, QObject *parent = nullptr);
    ~DataController();

    // Processes
    Q_INVOKABLE void insertData(const QVariantList &data, Enums::Data type);
    Q_INVOKABLE void removeData(const QVariantList &data, Enums::Data type);

    Q_INVOKABLE void resumeUnfinishedPending();
    Q_INVOKABLE void cancelUnfinishedPending();

    // Non processes
    Q_INVOKABLE bool containsData(const QVariantMap &modelData, Enums::Data data);

    bool processing() const;
    QSqlDatabase database(); // For testing

    void setQMLContext(QQmlApplicationEngine &engine);

signals:
    void processingChanged(const bool processing);

private:
    const QString m_corePath;

    std::unique_ptr<DatabaseController> m_databaseController;

    std::shared_ptr<ModelController> m_modelController;
    std::shared_ptr<FilesController> m_filesController;

    ProcessExecutor m_processExecutor;

    std::shared_ptr<Process> createInsertProcess(const QVariant &data, Enums::Data type);
    std::shared_ptr<Process> createRemoveProcess(const QVariant &data, Enums::Data type);

    void setupConnections();
    void searchForMissingDataAndRemove();
};

#endif // DATACONTROLLER_H
