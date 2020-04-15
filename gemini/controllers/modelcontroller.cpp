#include "modelcontroller.h"
#include "../models/sqltablemodel.h"
#include "../database/databasecore.h"

#include <QQmlContext>

Q_LOGGING_CATEGORY(modelController, "model.controller")

namespace {
    constexpr Enums::Data SONGS = Enums::Data::Songs;
    constexpr Enums::Data PLAYLIST = Enums::Data::Playlist;
    constexpr Enums::Data RELATIONS = Enums::Data::Relations;
    constexpr Enums::Data WALLPAPERS = Enums::Data::Wallpapers;
    constexpr Enums::Data PENDING = Enums::Data::Pending;
    constexpr Enums::Data UNKNOWN = Enums::Data::Unknown;
}

ModelController::ModelController(const QSqlDatabase &db, QObject *parent)
    : QObject(parent),
      m_database(db) {

    initializeModels();
}

void ModelController::appendData(const QVariantMap &data, Enums::Data type) {
    switch (type) {
        case SONGS:
            m_songModel->append(data);
            break;
        case PLAYLIST:
            m_playlistModel->append(data);
            break;
        case RELATIONS:
            m_relationModel->append(data);
            tryToUpdatePlaylist(data["playlist"].toInt());
            break;
        case WALLPAPERS:
            m_wallpaperModel->append(data);
            break;
        case PENDING:
            m_pendingModel->append(data);
            break;
        case UNKNOWN:
        default:
            qCWarning(modelController) << "appendData: Unknown data type!";
            break;
    }
}

void ModelController::erase(Enums::Data data) {
    switch (data) {
        case SONGS:
            m_songModel->erase();
            break;
        case PLAYLIST:
            m_playlistModel->erase();
            break;
        case RELATIONS:
            m_relationModel->erase();
            break;
        case WALLPAPERS:
            m_wallpaperModel->erase();
            break;
        case PENDING:
            m_pendingModel->erase();
            break;
        case UNKNOWN:
        default:
            qCWarning(modelController) << "clear: Unknown data type!";
            break;
    }
}

bool ModelController::contains(const QVariantMap &modelData, Enums::Data data) {
    switch (data) {
        case SONGS:
            return not m_songModel->find(modelData).isEmpty();
        case PLAYLIST:
            return not m_playlistModel->find(modelData).isEmpty();
        case RELATIONS:
            return not m_relationModel->find(modelData).isEmpty();
        case WALLPAPERS:
            return not m_wallpaperModel->find(modelData).isEmpty();
        case PENDING:
            qCWarning(modelController) << "contains: Pending Model does not support this operation";
            return false;
        case UNKNOWN:
        default:
            qCWarning(modelController) << "contains: Unknown data type!";
    }

    return false;
}

void ModelController::updateData(const QVariantMap &searchModelData, const QVariantMap &modelData, Enums::Data type) {
    switch (type) {
        case SONGS:
            m_songModel->updateData(searchModelData, modelData);
            break;
        case PLAYLIST:
            m_playlistModel->updateData(searchModelData, modelData);
            break;
        case RELATIONS:
            m_relationModel->updateData(searchModelData, modelData);
            break;
        case WALLPAPERS:
            m_wallpaperModel->updateData(searchModelData, modelData);
            break;
        case PENDING:
            m_pendingModel->updateData(searchModelData, modelData);
            break;
        case UNKNOWN:
        default:
            qCWarning(modelController) << "updateData: Unknown data type!";
            break;
    }
}

void ModelController::removeData(const QVariantMap &modelData, Enums::Data type) {
    switch (type) {
        case SONGS:
            m_songModel->remove(modelData);
            break;
        case PLAYLIST:
            m_playlistModel->remove(modelData);
            break;
        case RELATIONS:
            m_relationModel->remove(modelData);
            tryToUpdatePlaylist(modelData["playlist"].toInt());
            break;
        case WALLPAPERS:
            m_wallpaperModel->remove(modelData);
            break;
        case PENDING:
            m_pendingModel->remove(modelData);
            break;
        case UNKNOWN:
        default:
            qCWarning(modelController) << "updateData: Unknown data type!";
            break;
    }
}

QVariantList ModelController::readData(const QByteArray &roleName, Enums::Data data) {
    switch (data) {
        case SONGS:
            return m_songModel->read(roleName);
        case PLAYLIST:
            return m_playlistModel->read(roleName);
        case RELATIONS:
            return m_relationModel->read(roleName);
        case WALLPAPERS:
            return m_wallpaperModel->read(roleName);
        case PENDING:
            return m_pendingModel->read(roleName);
        case UNKNOWN:
        default:
            qCWarning(modelController) << "updateData: Unknown data type!";
            break;
    }

    return QVariantList();
}

QVariant ModelController::findBuddy(const QVariantMap &modelData, const QByteArray roleName, Enums::Data type) {
    switch (type) {
        case SONGS:
            return m_songModel->findBuddy(modelData, roleName);
        case PLAYLIST:
            return m_playlistModel->findBuddy(modelData, roleName);
        case WALLPAPERS:
            return m_wallpaperModel->findBuddy(modelData, roleName);
        case RELATIONS:
            qCWarning(modelController) << "findBuddy: Relations model does not support this operation!";
            return QVariant();
        case PENDING:
            qCWarning(modelController) << "findBuddy: Pending model does not support this operation!";
            return QVariant();
        case UNKNOWN:
        default:
            qCWarning(modelController) << "findBuddy: Unknown data type!";
            return QVariant();
            break;
    }
}

void ModelController::tryToUpdatePlaylist(const int id) {
    auto playlist = m_playlistModel->find({{"id", id}}, 1);

    if (not playlist.isEmpty()) {
        if (m_playlistModel->selectRow(playlist.first().row())) {
            qCInfo(modelController) << "Successfully updated playlist with id:" << id;
        }
    }
}

void ModelController::initializeModels() {
    m_wallpaperModel = std::shared_ptr<WallpaperModel>(new WallpaperModel(m_database), QObjectDeleter());
    m_playlistModel = std::shared_ptr<PlaylistModel>(new PlaylistModel(m_database), QObjectDeleter());
    m_songModel = std::shared_ptr<SongModel>(new SongModel(m_database), QObjectDeleter());
    m_relationModel = std::shared_ptr<RelationModel>(new RelationModel(m_database), QObjectDeleter());
    m_pendingModel = std::shared_ptr<PendingModel>(new PendingModel(m_database), QObjectDeleter());

    m_relationReadModel.setSourceModel(m_relationModel.get());
    m_songReadModel.setSourceModel(m_songModel.get());
    m_playlistReadModel.setSourceModel(m_playlistModel.get());
    m_wallpaperReadModel.setSourceModel(m_wallpaperModel.get());
    m_pendingReadModel.setSourceModel(m_pendingModel.get());

    m_songsInRelations = std::unique_ptr<SongsInRelations, QObjectDeleter>(new SongsInRelations(&m_songReadModel, &m_relationReadModel));
}

void ModelController::setQMLContext(QQmlApplicationEngine &engine) {
    engine.rootContext()->setContextProperty("playlistModel", &m_playlistReadModel);
    engine.rootContext()->setContextProperty("wallpaperModel", &m_wallpaperReadModel);
    engine.rootContext()->setContextProperty("songModel", &m_songReadModel);
    engine.rootContext()->setContextProperty("relationModel", &m_relationReadModel);
    engine.rootContext()->setContextProperty("pendingModel", &m_pendingReadModel);

    engine.rootContext()->setContextProperty("songsInRelations", m_songsInRelations.get());
}
