#include "datacontroller.h"

#include "../helpers/pathhelper.h"
#include "../common/utility.h"
#include "../common/deleters.h"

#include "../processes/insert/pendinginsertprocess.h"
#include "../processes/insert/playlistinsertprocess.h"
#include "../processes/insert/relationinsertprocess.h"
#include "../processes/insert/songinsertprocess.h"
#include "../processes/insert/wallpaperinsertprocess.h"

#include "../processes/insert/resumeunfinishedpendingprocess.h"

#include "../processes/remove/pendingremoveprocess.h"
#include "../processes/remove/playlistremoveprocess.h"
#include "../processes/remove/relationremoveprocess.h"
#include "../processes/remove/songremoveprocess.h"
#include "../processes/remove/wallpaperremoveprocess.h"

#include "../processes/remove/removemissingdataprocess.h"

#include <QQmlContext>
#include <QFileInfo>
#include <QDir>
#include <QStandardPaths>

Q_LOGGING_CATEGORY(dataController, "data.controller")

namespace {
    constexpr Enums::Data PLAYLIST = Enums::Data::Playlist;
    constexpr Enums::Data SONGS = Enums::Data::Songs;
    constexpr Enums::Data RELATIONS = Enums::Data::Relations;
    constexpr Enums::Data WALLPAPERS = Enums::Data::Wallpapers;
    constexpr Enums::Data PENDING = Enums::Data::Pending;
    constexpr Enums::Data UNKNOWN = Enums::Data::Unknown;
}

DataController::DataController(QObject *parent)
    : QObject(parent),
      m_corePath(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)) {

#ifdef ERASE_DATA
    if (QFileInfo(m_corePath).exists()) {
        QDir(m_corePath).removeRecursively();
    }
#endif

    if (not QFileInfo(m_corePath).exists()) {
        QFileInfo(m_corePath).absoluteDir().mkpath(".");
    }

    m_databaseController = std::unique_ptr<DatabaseController>(new DatabaseController(m_corePath));
    m_modelController = std::shared_ptr<ModelController>(new ModelController(m_databaseController->database()), QObjectDeleter());
    m_filesController = std::shared_ptr<FilesController>(new FilesController(m_corePath), QObjectDeleter());

    setupConnections();
    searchForMissingDataAndRemove();
}

DataController::DataController(const QString &corePath, QObject *parent)
    : QObject(parent),
      m_corePath(corePath) {

#ifdef ERASE_DATA
    if (QFileInfo(m_corePath).exists()) {
        QDir(m_corePath).removeRecursively();
    }
#endif

    if (not QFileInfo(m_corePath).exists()) {
        QFileInfo(m_corePath).absoluteDir().mkpath(".");
    }

    m_databaseController = std::unique_ptr<DatabaseController>(new DatabaseController(m_corePath));
    m_modelController = std::shared_ptr<ModelController>(new ModelController(m_databaseController->database()), QObjectDeleter());
    m_filesController = std::shared_ptr<FilesController>(new FilesController(m_corePath), QObjectDeleter());

    setupConnections();
    searchForMissingDataAndRemove();
}

DataController::~DataController() {
    if (m_processExecutor.isRunning()) {
        m_processExecutor.terminate();
        m_processExecutor.wait();
    }
}

bool DataController::processing() const {
    return m_processExecutor.isRunning();
}

QSqlDatabase DataController::database() {
    return m_databaseController->database();
}

std::shared_ptr<Process> DataController::createInsertProcess(const QVariant &data, Enums::Data type) {
    switch (type) {
        case PLAYLIST:
            return std::shared_ptr<Process>(new PlaylistInsertProcess(m_modelController, data));
        case SONGS:
            return std::shared_ptr<Process>(new SongInsertProcess(m_modelController, m_filesController, data));
        case RELATIONS:
            return std::shared_ptr<Process>(new RelationInsertProcess(m_modelController, m_filesController, data));
        case WALLPAPERS:
            return std::shared_ptr<Process>(new WallpaperInsertProcess(m_modelController, m_filesController, data));
        case PENDING:
            return std::shared_ptr<Process>(new PendingInsertProcess(m_modelController, data));
        case UNKNOWN:
        default:
            qCWarning(dataController) << "createInsertProcess: Unknown data type!";
            return std::shared_ptr<Process>(nullptr);
    }
}

std::shared_ptr<Process> DataController::createRemoveProcess(const QVariant &data, Enums::Data type) {
    switch (type) {
        case PLAYLIST:
            return std::shared_ptr<Process>(new PlaylistRemoveProcess(m_modelController, data));
        case SONGS:
            return std::shared_ptr<Process>(new SongRemoveProcess(m_modelController, m_filesController, data));
        case RELATIONS:
            return std::shared_ptr<Process>(new RelationRemoveProcess(m_modelController, m_filesController, data));
        case WALLPAPERS:
            return std::shared_ptr<Process>(new WallpaperRemoveProcess(m_modelController, m_filesController, data));
            break;
        case PENDING:
            return std::shared_ptr<Process>(new PendingRemoveProcess(m_modelController));
        case UNKNOWN:
        default:
            qCWarning(dataController) << "createDeleteProcess: Unknown data type!";
            return std::shared_ptr<Process>(nullptr);
    }
}

void DataController::insertData(const QVariantList &data, Enums::Data type) {
    if (m_processExecutor.isRunning()) {
        qCWarning(dataController) << "Data controller is already processing";
        return;
    }

    for (const auto &item : qAsConst(data)) {
        m_processExecutor.appendProcess(createInsertProcess(item, type));
    }

    if (Utility::isPendable(type)) {
        m_processExecutor.prependProcess(createInsertProcess(data, PENDING));
        m_processExecutor.appendProcess(createRemoveProcess(data, PENDING));
    }

    m_processExecutor.start();
}

void DataController::removeData(const QVariantList &data, Enums::Data type) {
    if (m_processExecutor.isRunning()) {
        qCWarning(dataController) << "Data controller is already processing";
        return;
    }

    for (const auto &item : qAsConst(data)) {
        m_processExecutor.appendProcess(createRemoveProcess(item, type));
    }

    m_processExecutor.start();
}

void DataController::resumeUnfinishedPending() {
    if (m_processExecutor.isRunning()) {
        qCWarning(dataController) << "Data controller is already processing";
        return;
    }

    m_processExecutor.appendProcess(std::shared_ptr<ResumeUnfinishedPendingProcess>(new ResumeUnfinishedPendingProcess(m_modelController, m_filesController)));
    m_processExecutor.start();
}

void DataController::cancelUnfinishedPending() {
    if (m_processExecutor.isRunning()) {
        qCWarning(dataController) << "Data controller is already processing";
        return;
    }

    m_processExecutor.appendProcess(std::shared_ptr<PendingRemoveProcess>(new PendingRemoveProcess(m_modelController)));
    m_processExecutor.start();
}

void DataController::searchForMissingDataAndRemove() {
    qCInfo(dataController) << "Searching for missing data";

    m_processExecutor.appendProcess(std::shared_ptr<Process>(new RemoveMissingDataProcess(m_modelController)));
    m_processExecutor.start();
}

bool DataController::containsData(const QVariantMap &modelData, Enums::Data data) {
    return m_modelController->contains(modelData, data);
}

void DataController::setQMLContext(QQmlApplicationEngine &engine) {
    m_modelController->setQMLContext(engine);
}

void DataController::setupConnections() {
    connect(&m_processExecutor, &ProcessExecutor::processingChanged,
            this, &DataController::processingChanged);
}
