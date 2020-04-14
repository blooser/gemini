#include <QtTest>

#include <QtSql/QSqlDatabase>
#include <QDir>

#include <models/relationmodel.h>
#include <models/songmodel.h>
#include <models/wallpapermodel.h>
#include <models/playlistmodel.h>
#include <models/pendingmodel.h>

#include <models/proxy/readmodel.h>

#include <models/proxy/songsinrelations.h>

#include <database/databasecore.h>
#include <database/databasetables.h>

class ModelsTest : public QObject {
    Q_OBJECT

public:
    ModelsTest();
    ~ModelsTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testModelAppendValues();
    void testModelFindValues();
    void testModelFindBuddy();
    void testModelRemoveValue();
    void testModelEraseAllData();
    void testModelReadSelectedData();

    void testReadModelEmitsSizeChangedSignal();

    void testSongsInRelationsProxyModelFilterSongs();

private:
    QSqlDatabase db;
};

ModelsTest::ModelsTest() {

}

ModelsTest::~ModelsTest() {

}

void ModelsTest::initTestCase() {
    database::core::setup(db, "", ":memory:");
    QVERIFY(db.isValid());
}

void ModelsTest::cleanupTestCase() {

}

void ModelsTest::init() {
    db.open();
    QVERIFY(db.isOpen());

    for (const auto &table : qAsConst(database::Tables)) {
        table(db);
    }

    QVERIFY(!db.tables().isEmpty());

    QStringList expectedTables {
        "wallpapers", "playlists", "songs", "relations", "pending"
    };

    for (const auto &table : qAsConst(expectedTables)) {
        QVERIFY(db.tables().contains(table));
    }
}

void ModelsTest::cleanup() {
    db.close();
    QVERIFY(!db.isOpen());
}

void ModelsTest::testModelAppendValues() {
    PlaylistModel playlistModel(db);
    QCOMPARE(playlistModel.tableName(), QStringLiteral("playlists"));
    QCOMPARE(playlistModel.rowCount(), 0);

    QVector<QVariantMap> modelDatas = {
        {
            { "name", "test1" },
        },
        {
            { "name", "test2" },
        },
        {
            { "name", "test3" },
        },
        {
            { "name", "test4" },
        },
        {
            { "name", "test5" },
        }
    };

    for (const auto &modelData : qAsConst(modelDatas)) {
        playlistModel.append(modelData);
    }

    QCOMPARE(playlistModel.rowCount(), 5);
}

void ModelsTest::testModelFindValues() {
    RelationModel relationModel(db);
    QCOMPARE(relationModel.tableName(), QStringLiteral("relations"));

    QVector<QVariantMap> modelDatas = {
        {
            { "playlist", 4 },
            { "song", 2 }
        },

        {
            { "playlist", 7 },
            { "song", 1 }
        },

        {
            { "playlist", 7 },
            { "song", 2 }
        },
    };

    for (const auto &modelData : qAsConst(modelDatas)) {
        relationModel.append(modelData);
    }

    const QVariantMap searchModelData = {
        { "playlist", 7 },
        { "song", 2 }
    };

    auto indexes = relationModel.find(searchModelData);
    QVERIFY(!indexes.isEmpty());
    QCOMPARE(indexes.size(), 1);
    QCOMPARE(indexes.back().row(), 2);
}

void ModelsTest::testModelReadSelectedData() {
    RelationModel relationModel(db);
    QCOMPARE(relationModel.tableName(), QStringLiteral("relations"));

    QVector<QVariantMap> modelDatas = {
       {
           { "playlist", "playlist1" },
           { "song", "song1" }
       },
       {
            { "playlist", "playlist1" },
            { "song", "song2" }
       },
       {
            { "playlist", "playlist1" },
            { "song", "song3" }
       }
    };

    for (const auto &data : qAsConst(modelDatas)) {
        relationModel.append(data);
    }

    QCOMPARE(relationModel.rowCount(), 3);

    auto songs = relationModel.read("song");
    QVERIFY(songs.size());
    QCOMPARE(songs.size(), 3);

    QVariantList expectesSongs {
        "song1", "song2", "song3"
    };

    for (int i=0; i<expectesSongs.size(); ++i) {
        QCOMPARE(songs.at(i), expectesSongs.at(i));
    }
}

void ModelsTest::testModelFindBuddy() {
    SongModel songModel(db);
    QCOMPARE(songModel.tableName(), QStringLiteral("songs"));

    QVector<QVariantMap> modelDatas = {
       {
           { "url", "file:///foo/bar/test1" },
           { "title", "test1" },
           { "duration", 500 }
       },
       {
            { "url", "file:///foo/bar/test2" },
            { "title", "test2" },
            { "duration", 500 }
       },
       {
            { "url", "file:///foo/bar/test3" },
            { "title", "test3" },
            { "duration", 500 }
       }
    };

    for (const auto &modelData : qAsConst(modelDatas)) {
        songModel.append(modelData);
    }

    songModel.select();
    QCOMPARE(songModel.rowCount(), 3);

    const QVariantMap searchModelData = {
        { "title", "test3" }
    };

    auto buddy = songModel.findBuddy(searchModelData, "url");
    QVERIFY(buddy.isValid());
    QCOMPARE(buddy.toString(), QStringLiteral("file:///foo/bar/test3"));
}

void ModelsTest::testModelRemoveValue() {
    WallpaperModel wallpaperModel(db);
    QCOMPARE(wallpaperModel.tableName(), QStringLiteral("wallpapers"));

    QVector<QVariantMap> modelDatas = {
        {
           { "url", "file:///foo/bar/test1" },
           { "name", "test1" },
           { "duration", 500 }
        },
        {
            { "url", "file:///foo/bar/test2" },
            { "name", "test2" },
            { "duration", 500 }
        },
        {
            { "url", "file:///foo/bar/test3" },
            { "name", "test3" },
            { "duration", 500 }
        }
    };

    for (const auto &modelData : qAsConst(modelDatas)) {
        wallpaperModel.append(modelData);
    }

    const QVariantMap dataToRemove = {
        { "url", "file:///foo/bar/test2" },
    };

    QCOMPARE(wallpaperModel.rowCount(), 3);
    wallpaperModel.remove(dataToRemove);
    QCOMPARE(wallpaperModel.rowCount(), 2);
}

void ModelsTest::testModelEraseAllData() {
    PendingModel pendingModel(db);
    QCOMPARE(pendingModel.tableName(), QStringLiteral("pending"));

    QVector<QVariantMap> modelDatas = {
        {
           { "url", "file:///foo/bar/test1" },
           { "done", 1 }
        },
        {
           { "url", "file:///foo/bar/test2" },
           { "done", 1 }
        },
    };

    for (const auto &modelData : qAsConst(modelDatas)) {
        pendingModel.append(modelData);
    }

    QCOMPARE(pendingModel.rowCount(), 2);
    QVERIFY(pendingModel.erase());
    QCOMPARE(pendingModel.rowCount(), 0);
}

void ModelsTest::testReadModelEmitsSizeChangedSignal() {
    SongModel songModel(db);
    QVector<QVariantMap> songModelData = {
        {
           { "url", "file:///foo/bar/song1" },
           { "title", "song1" },
           { "duration", 500 }
        },
        {
           { "url", "file:///foo/bar/song2" },
           { "title", "song2" },
           { "duration", 500 }
        },
        {
           { "url", "file:///foo/bar/song3" },
           { "title", "song3" },
           { "duration", 500 }
        },
    };


    ReadModel readModel;
    QSignalSpy spy(&readModel, &ReadModel::sizeChanged);
    readModel.setSourceModel(&songModel);

    for (const auto &modelData : qAsConst(songModelData)) {
        songModel.append(modelData);
    }

    QCOMPARE(readModel.rowCount(), 3);
    QCOMPARE(spy.count(), 3);

    for (const auto &modelData : qAsConst(songModelData)) {
        songModel.remove(modelData);
    }

    QCOMPARE(readModel.rowCount(), 0);
    QCOMPARE(spy.count(), 6);
}

void ModelsTest::testSongsInRelationsProxyModelFilterSongs() {
    SongModel songModel(db);
    QVector<QVariantMap> songModelData = {
        {
           { "url", "file:///foo/bar/song1" },
           { "title", "song1" },
           { "duration", 500 }
        },
        {
           { "url", "file:///foo/bar/song2" },
           { "title", "song2" },
           { "duration", 500 }
        },
        {
           { "url", "file:///foo/bar/song3" },
           { "title", "song3" },
           { "duration", 500 }
        },
    };

    for (const auto &modelData : qAsConst(songModelData)) {
        songModel.append(modelData);
    }

    QCOMPARE(songModel.rowCount(), 3);

    RelationModel relationModel(db);
    QVector<QVariantMap> relationsModelData = {
        {
            { "playlist", 7 },
            { "song", 1 }
        },
        {
            { "playlist", 7 },
            { "song", 2 }
        },
        {
            { "playlist", 8 },
            { "song", 2 }
        },

    };

    for (const auto &modelData : qAsConst(relationsModelData)) {
        relationModel.append(modelData);
    }

    QCOMPARE(relationModel.rowCount(), 3);

    SongsInRelations songsInRelation(&songModel, &relationModel);
    songsInRelation.setCurrentPlaylist({8, ""});
    QCOMPARE(songsInRelation.rowCount(), 1);
    songsInRelation.setCurrentPlaylist({7, ""});
    QCOMPARE(songsInRelation.rowCount(), 2);
    songsInRelation.setCurrentPlaylist({6, ""});
    QCOMPARE(songsInRelation.rowCount(), 0);
}

QTEST_APPLESS_MAIN(ModelsTest)

#include "tst_modelstest.moc"
