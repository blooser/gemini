#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "../common/deleters.h"
#include "../common/enums.h"

#include "../models/wallpapermodel.h"
#include "../models/playlistmodel.h"
#include "../models/songmodel.h"
#include "../models/relationmodel.h"
#include "../models/pendingmodel.h"

#include "../models/proxy/readmodel.h"
#include "../models/proxy/songsinrelations.h"

#include "../data/playlistdata.h"

#include <memory>

#include <QObject>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(modelController)

class ModelController : public QObject {
    Q_OBJECT

public:
    explicit ModelController(const QSqlDatabase &db, QObject *parent=nullptr);

    void appendData(const QVariantMap &modelData, Enums::Data type);
    void updateData(const QVariantMap &searchModelData, const QVariantMap &modelData, Enums::Data type);
    void removeData(const QVariantMap &modelData, Enums::Data type);
    QVariantList readData(const QByteArray &roleName, Enums::Data data);
    void erase(Enums::Data data);
    bool contains(const QVariantMap &modelData, Enums::Data data);
    QVariantList findBuddy(const QVariantMap &modelData, const QByteArray roleName, Enums::Data type, int hints=1);

    void setQMLContext(QQmlApplicationEngine &engine);

protected:
    void refresh(Enums::Data data);

private:
    QSqlDatabase m_database;
    std::shared_ptr<WallpaperModel> m_wallpaperModel;
    std::shared_ptr<PlaylistModel> m_playlistModel;
    std::shared_ptr<SongModel> m_songModel;
    std::shared_ptr<RelationModel> m_relationModel;
    std::shared_ptr<PendingModel> m_pendingModel;

    std::unique_ptr<SongsInRelations, QObjectDeleter> m_songsInRelations;

    ReadModel m_relationReadModel;
    ReadModel m_songReadModel;
    ReadModel m_playlistReadModel;
    ReadModel m_wallpaperReadModel;
    ReadModel m_pendingReadModel;

    void initializeModels();
};

#endif // MODELMANAGER_H
