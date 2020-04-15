#include <QtTest>
#include <QtSql/QSqlDatabase>

#include <controllers/modelcontroller.h>

#include <database/databasecore.h>
#include <database/databasetables.h>

class ModelControllerTest : public QObject
{
    Q_OBJECT

public:
    ModelControllerTest();
    ~ModelControllerTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testModelControllerRefreshValidPlaylistWhenRelationsIsChanging();

private:
    QSqlDatabase db;

};

ModelControllerTest::ModelControllerTest()
{

}

ModelControllerTest::~ModelControllerTest()
{

}

void ModelControllerTest::initTestCase() {
    database::core::setup(db, "", ":memory:");
    QVERIFY(db.isValid());
}

void ModelControllerTest::cleanupTestCase()
{

}

void ModelControllerTest::init() {
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

    for (const auto &trigger : qAsConst(database::Triggers)) {
        trigger(db);
    }
}

void ModelControllerTest::cleanup() {
    db.close();
    QVERIFY(!db.isOpen());
}

void ModelControllerTest::testModelControllerRefreshValidPlaylistWhenRelationsIsChanging() {
    ModelController modelController(db);

    QVariantMap playlistData = {
        {"name", "best"},
        {"songs", 0}
    };

    QVector<QVariantMap> songData = {
        {
            {"title", "song1"},
            {"duration", 100},
            {"url", "/foo/bar/path"}
        },

        {
            {"title", "song2"},
            {"duration", 100},
            {"url", "/foo/bar/path2"}
        },

        {
            {"title", "song3"},
            {"duration", 100},
            {"url", "/foo/bar/path3"}
        }
    };

    modelController.appendData(playlistData, Enums::Data::Playlist);

    for (const auto &song : qAsConst(songData)) {
        modelController.appendData(song, Enums::Data::Songs);
    }

    PlaylistModel playlistModel(db);
    QCOMPARE(playlistModel.rowCount(), 1);

    SongModel songModel(db);
    QCOMPARE(songModel.rowCount(), 3);

    QVector<QVariantMap> relationsData = {
        {
            {"playlist", 1},
            {"song", 1}
        },

        {
            {"playlist", 1},
            {"song", 2}
        },

        {
            {"playlist", 1},
            {"song", 3}
        },
    };

    QVector<QVariantMap> expectedValues = {
        {
            {"songs", 1}, // NOTE: songs are increasing by 1
            {"duration", 100} // NOTE: duration is increasing by 100
        },

        {
            {"songs", 2},
            {"duration", 200}
        },

        {
            {"songs", 3},
            {"duration", 300}
        }
    };

    int i = 0;
    for (const auto &relationData : qAsConst(relationsData)) {
        modelController.appendData(relationData, Enums::Data::Relations);
        // NOTE: There is only one playlist
        QCOMPARE(modelController.readData("songs", Enums::Data::Playlist).toVector().at(0).toInt(), expectedValues[i]["songs"]);
        QCOMPARE(modelController.readData("duration", Enums::Data::Playlist).toVector().at(0).toInt(), expectedValues[i]["duration"]);

        ++i;
    }
}


QTEST_APPLESS_MAIN(ModelControllerTest)

#include "tst_modelcontrollertest.moc"
