#include <QtQuickTest/quicktest.h>

#include <memory>

#include <QQmlEngine>
#include <QQmlContext>
#include <QSqlDatabase>

#include <tools/playlist.h>
#include <models/playlistmodel.h>
#include <models/songmodel.h>
#include <database/databasecore.h>
#include <database/databasetables.h>

class Setup : public QObject {
    Q_OBJECT

public:
    Setup() {
        database::core::setup(db, "", ":memory:");

        for (const auto &table : qAsConst(database::Tables)) {
            table(db);
        }


        playlistModel = std::unique_ptr<PlaylistModel>(new PlaylistModel(db));

        QVector<QVariantMap> playlists {
            {
                {"name", "playlist1"}
            },
            {
                {"name", "playlist2"}
            }
        };

        for (const auto &playlist : qAsConst(playlists)) {
            playlistModel->append(playlist);
        }

        songModel = std::unique_ptr<SongModel>(new SongModel(db));

        QVector<QVariantMap> modelDatas {
            {
                { "name", "song1" },
                { "url", "/foo/path1" }
            },
            {
                { "name", "song2" },
                { "url", "/foo/path2" }
            }
        };

        for (const auto &modelData : qAsConst(modelDatas)) {
            songModel->append(modelData);
        }
    }

public slots:
    void qmlEngineAvailable(QQmlEngine *engine) {
        engine->rootContext()->setContextProperty("playlistModel", playlistModel.get());
        engine->rootContext()->setContextProperty("songModel", songModel.get());
    }

    void applicationAvailable() {
        qmlRegisterType<Playlist>("com.gemini.tools", 0, 1, "Playlist");
    }

private:
    QSqlDatabase db;
    std::unique_ptr<PlaylistModel> playlistModel;
    std::unique_ptr<SongModel> songModel;
};

QUICK_TEST_MAIN_WITH_SETUP(PlaylistQuickTest, Setup)

#include "quicktest_playlist.moc"
