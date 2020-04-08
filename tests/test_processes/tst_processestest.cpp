#include <QtTest>

#include <QtSql/QSqlDatabase>
#include <QDir>

#include <QQmlApplicationEngine>

#include <memory>

#include <database/databasecore.h>
#include <database/databasetables.h>

#include <controllers/modelcontroller.h>
#include <controllers/filescontroller.h>

#include <processes/insert/pendinginsertprocess.h>
#include <processes/insert/playlistinsertprocess.h>
#include <processes/insert/relationinsertprocess.h>
#include <processes/insert/songinsertprocess.h>
#include <processes/insert/wallpaperinsertprocess.h>

#include <processes/insert/resumeunfinishedpendingprocess.h>

#include <processes/remove/pendingremoveprocess.h>
#include <processes/remove/playlistremoveprocess.h>
#include <processes/remove/relationremoveprocess.h>
#include <processes/remove/songremoveprocess.h>
#include <processes/remove/wallpaperremoveprocess.h>

#include <processes/remove/removemissingdataprocess.h>

class ProcessesTest : public QObject {
    Q_OBJECT

public:
    ProcessesTest();
    ~ProcessesTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testPendingProcessInsertAndRemoveData();
    void testPendingProcessHandlesInsertInvalidData();
    void testPlaylistProcessInsertAndRemoveDataFromPlaylistAndRelationModel();
    void testPlaylistProcessHandlesInsertInvalidData();
    void testPlaylistProcessHandlesRemoveInvalidData();
    void testRelationProcessInsertAndRemoveData();
    void testRelationProcessInsertAndRemoveDataWithFiles();
    void testRelationProcessHandlesInsertInvalidData();
    void testRelationProcessHandlesRemoveInvalidData();
    void testSongProcessInsertAndRemoveDataFromSongAndRelationModel();
    void testSongProcessInsertSongWithParsedMeta();
    void testSongProcessHandlesInsertInvalidData();
    void testSongProcessHandlesRemoveInvalidData();
    void testWallpaperProcessInsertAndRemoveData();
    void testWallpaperProcessHandlesInsertInvalidData();
    void testWallpaperProcessHandlesRemoveInvalidData();
    void testResumeUnfinishedPendingProcessResumeAndRunUnfinishedInsertProcesses();
    void testRemoveMissingDataRemovesMissingData();

private:
    const QString path;
    const QUrl tmpSong;
    const QUrl tmpWallpaper;
    const QUrl expectedSong;
    const QUrl expectedWallpaper;
    QSqlDatabase db;
    std::shared_ptr<ModelController> modelController;
    std::shared_ptr<FilesController> filesController;
};

ProcessesTest::ProcessesTest()
    : path(QDir::currentPath()),
      tmpSong(QUrl::fromLocalFile(path + "/files/song.mp3")),
      tmpWallpaper(QUrl::fromLocalFile(path + "/files/wallpaper.jpeg")),
      expectedSong(QUrl::fromLocalFile(path + "/songs/song.mp3")),
      expectedWallpaper(QUrl::fromLocalFile(path + "/wallpapers/wallpaper.jpeg")) {
}

ProcessesTest::~ProcessesTest() {

}

void ProcessesTest::initTestCase() {
    database::core::setup(db, "", ":memory:");
    QVERIFY(db.isValid());

    QFile songFile(":/song");
    QVERIFY(songFile.open(QIODevice::ReadOnly));

    QVERIFY(QFileInfo(tmpSong.path()).dir().mkpath("."));
    QFile file(tmpSong.path());
    QVERIFY(file.open(QIODevice::WriteOnly));
    file.write(songFile.readAll());
    file.close();
    songFile.close();

    file.setFileName(tmpWallpaper.path());
    QVERIFY(file.open(QIODevice::WriteOnly));
    file.write("01010101001");
    file.close();
}

void ProcessesTest::cleanupTestCase() {
    QDir remover(path + "/songs");
    QVERIFY(remover.removeRecursively());

    remover.setPath(path + "/wallpapers");
    QVERIFY(remover.removeRecursively());

    remover.setPath(path + "/files");
    QVERIFY(remover.removeRecursively());
}

void ProcessesTest::init() {
    db.open();
    QVERIFY(db.isOpen());

    for (const auto &table : database::Tables) {
        table(db);
    }

    QStringList expectedTables {
        "wallpapers", "playlists", "songs", "relations", "pending"
    };

    for (const auto &table : qAsConst(expectedTables)) {
        QVERIFY(db.tables().contains(table));
    }

    modelController.reset(new ModelController(db));
    QVERIFY(modelController);

    filesController.reset(new FilesController(path));
    QVERIFY(filesController);

    QVERIFY(QFileInfo(tmpSong.path()).exists());
    QVERIFY(QFileInfo(tmpSong.path()).exists());
}

void ProcessesTest::cleanup() {
    db.close();
    QVERIFY(!db.isOpen());

    if (QFileInfo(expectedSong.path()).exists()) {
        QVERIFY(QFile::remove(expectedSong.path()));
    }

    if (QFileInfo(expectedWallpaper.path()).exists()) {
        QVERIFY(QFile::remove(expectedWallpaper.path()));
    }
}

void ProcessesTest::testPendingProcessInsertAndRemoveData() {
    QStringList files {
        "/foo/bar/tst1", "/foo/bar/tst2", "/foo/bar/tst3", "/foo/bar/tst4", "/foo/bar/tst5"
    };

    QVariant data = QVariant::fromValue(QStringList(files));

    std::unique_ptr<PendingInsertProcess> pendingInsert(new PendingInsertProcess(modelController, data));
    pendingInsert->start();

    PendingModel pendingModel(db);
    QCOMPARE(pendingModel.rowCount(), files.size());

    std::unique_ptr<PendingRemoveProcess> pendingRemove(new PendingRemoveProcess(modelController));
    pendingRemove->start();

    pendingModel.select();

    QCOMPARE(pendingModel.rowCount(), 0);
}

void ProcessesTest::testPendingProcessHandlesInsertInvalidData() {
    constexpr int expectedSize = 1;
    QVariantList invalidData {
        QUrl(":/foo/bar"), 24, "", "/foo/bar/valid"
    };

    std::unique_ptr<PendingInsertProcess> pendingInsert(new PendingInsertProcess(modelController, invalidData));
    pendingInsert->start();

    PendingModel pendingModel(db);
    QCOMPARE(pendingModel.rowCount(), expectedSize);
}

void ProcessesTest::testPlaylistProcessInsertAndRemoveDataFromPlaylistAndRelationModel() {
    QVariant data = QVariant("Best");
    constexpr int expectedPlaylistId = 1;
    std::unique_ptr<PlaylistInsertProcess> playlistInsert(new PlaylistInsertProcess(modelController, data));
    playlistInsert->start();

    PlaylistModel playlistModel(db);
    QCOMPARE(playlistModel.rowCount(), 1);

    QVariantMap relationData = {
        { "playlist", expectedPlaylistId },
        { "song", 15 }
    };

    std::unique_ptr<RelationInsertProcess> relationInsert(new RelationInsertProcess(modelController, filesController, relationData));
    relationInsert->start();

    RelationModel relationModel(db);
    QCOMPARE(relationModel.rowCount(), 1);

    std::unique_ptr<PlaylistRemoveProcess> playlistRemove(new PlaylistRemoveProcess(modelController, expectedPlaylistId));
    playlistRemove->start();

    relationModel.select();
    playlistModel.select();

    QCOMPARE(playlistModel.rowCount(), 0);
    QCOMPARE(relationModel.rowCount(), 0);
}

void ProcessesTest::testPlaylistProcessHandlesInsertInvalidData() {
    QString invalidData = QStringLiteral("");
    constexpr int expectedSize = 0;
    std::unique_ptr<PlaylistInsertProcess> playlistInsert(new PlaylistInsertProcess(modelController, invalidData));
    playlistInsert->start();

    PlaylistModel playlistModel(db);
    QCOMPARE(playlistModel.rowCount(), expectedSize);
}

void ProcessesTest::testPlaylistProcessHandlesRemoveInvalidData() {
    constexpr int expectedSize = 2;
    QVariantList insertData {
        "Playlist1", "Playlist2"
    };

    for (const auto &data : qAsConst(insertData)) {
        std::unique_ptr<PlaylistInsertProcess> playlistInsert(new PlaylistInsertProcess(modelController, data));
        playlistInsert->start();
    }

    PlaylistModel playlistModel(db);
    QCOMPARE(playlistModel.rowCount(), expectedSize);

    QVariantList removeData {
        QUrl("/foo/bar"), "playlist", 10
    };

    for (const auto &data : qAsConst(removeData)) {
        std::unique_ptr<PlaylistRemoveProcess> playlistRemove(new PlaylistRemoveProcess(modelController, data));
        playlistRemove->start();
    }

    playlistModel.select();
    QCOMPARE(playlistModel.rowCount(), expectedSize);
}

void ProcessesTest::testRelationProcessInsertAndRemoveData() {
    QVector<QVariantMap> vectorData {
        {
            { "playlist", 1 },
            { "song", 1 }
        },
        {
            { "playlist", 2 },
            { "song", 2 }
        },
        {
            { "playlist", 2 },
            { "song", 3 }
        }
    };

    for (const auto &data : qAsConst(vectorData)) {
        std::unique_ptr<RelationInsertProcess> insertProcess(new RelationInsertProcess(modelController, filesController, data));
        insertProcess->start();
    }

    RelationModel relationModel(db);
    QCOMPARE(relationModel.rowCount(), 3);

    QVariantMap data = {
        { "playlist", 2 },
        { "song", 2 }
    };

    std::unique_ptr<RelationRemoveProcess> removeProcess(new RelationRemoveProcess(modelController, filesController, data));
    removeProcess->start();

    relationModel.select();

    QCOMPARE(relationModel.rowCount(), 2);
}

void ProcessesTest::testRelationProcessHandlesInsertInvalidData() {
    constexpr int expectedSize = 1;
    QVariantList invalidData {
        1,
        "",
        false,
        QVariantMap { // Valid
            {"playlist", 1},
            {"song", 2}
        }
    };

    for (const auto &data : qAsConst(invalidData)) {
        std::unique_ptr<RelationInsertProcess> insertProcess(new RelationInsertProcess(modelController, filesController, data));
        insertProcess->start();
    }

    RelationModel relationModel(db);
    QCOMPARE(relationModel.rowCount(), expectedSize);
}

void ProcessesTest::testRelationProcessHandlesRemoveInvalidData() {
    constexpr int expectedSize = 2;

    QVariantList insertData {
        QVariantMap {
            {"playlist", 1},
            {"song", 1}
        },

        QVariantMap {
            {"playlist", 2},
            {"song", 1}
        }
    };

    for (const auto &data : qAsConst(insertData)) {
        std::unique_ptr<RelationInsertProcess> insertProcess(new RelationInsertProcess(modelController, filesController, data));
        insertProcess->start();
    }

    RelationModel relationModel(db);
    QCOMPARE(relationModel.rowCount(), expectedSize);

    QVariantList removeData {
        56,
        QUrl("/foo/bar2"),
        false,
        "",
    };

    for (const auto &data : qAsConst(removeData)) {
        std::unique_ptr<RelationRemoveProcess> relationRemove(new RelationRemoveProcess(modelController, filesController, data));
        relationRemove->start();
    }

    relationModel.select();
    QCOMPARE(relationModel.rowCount(), expectedSize);
}

void ProcessesTest::testRelationProcessInsertAndRemoveDataWithFiles() {
    QVariantMap data = {
        { "playlist", 1 },
        { "files", QVariantList() << tmpSong }
    };

    std::unique_ptr<RelationInsertProcess> relationInsert(new RelationInsertProcess(modelController, filesController, data));
    relationInsert->start();

    RelationModel relationModel(db);
    SongModel songModel(db);

    QCOMPARE(relationModel.rowCount(), 1);
    QCOMPARE(songModel.rowCount(), 1);
    QVERIFY(QFileInfo(expectedSong.path()).exists());

    data = {
        { "playlist", 1  },
        { "song", 1 }
    };

    std::unique_ptr<RelationRemoveProcess> relationRemove(new RelationRemoveProcess(modelController, filesController, data));
    relationRemove->start();

    relationModel.select();

    QCOMPARE(relationModel.rowCount(), 0);
    QVERIFY(QFile::remove(expectedSong.path()));
}

void ProcessesTest::testSongProcessInsertAndRemoveDataFromSongAndRelationModel() {
    std::unique_ptr<SongInsertProcess> songInsert(new SongInsertProcess(modelController, filesController, tmpSong));
    songInsert->start();

    SongModel songModel(db);
    QCOMPARE(songModel.rowCount(), 1);
    QVERIFY(QFileInfo(expectedSong.path()).exists());

    QVariantMap relationModelData {
        { "playlist", 1 },
        { "song", 1 }
    };

    std::unique_ptr<RelationInsertProcess> relationInsert(new RelationInsertProcess(modelController, filesController, relationModelData));
    relationInsert->start();

    RelationModel relationModel(db);
    QCOMPARE(relationModel.rowCount(), 1);

    constexpr int expectedSongId = 1;
    QVariantMap removeSongModelData {
        { "id", expectedSongId },
        { "url", expectedSong }
    };
    std::unique_ptr<SongRemoveProcess> songRemove(new SongRemoveProcess(modelController, filesController, removeSongModelData));
    songRemove->start();

    songModel.select();
    relationModel.select();

    QCOMPARE(songModel.rowCount(), 0);
    QCOMPARE(relationModel.rowCount(), 0);
    QVERIFY(!QFileInfo(expectedSong.path()).exists());
}

void ProcessesTest::testSongProcessInsertSongWithParsedMeta() {
    std::unique_ptr<SongInsertProcess> songInsert(new SongInsertProcess(modelController, filesController, tmpSong));
    songInsert->start();

    SongModel songModel(db);
    QCOMPARE(songModel.rowCount(), 1);

    // These values are in meta info of song.mp3 (check testresources/song.mp3)
    QVector<QPair<QByteArray, QVariant>> expectedValues = {
        { "title", "TestSong" },
        { "duration", 261 },
        { "artist", "Test" },
        { "date", 2006 },
        { "album", "testing" },
        { "genre", "Dream" },
        { "url", expectedSong },
    };

    auto index = songModel.index(0, 0);
    for (const auto value : qAsConst(expectedValues)) {
        QCOMPARE(songModel.data(index, songModel.roleNames().key(value.first)), value.second);
    }
}

void ProcessesTest::testSongProcessHandlesInsertInvalidData() {
    constexpr int expectedSize = 0;
    constexpr double invalidData = 0.00;
    std::unique_ptr<SongInsertProcess> songInsert(new SongInsertProcess(modelController, filesController, invalidData));
    songInsert->start();

    SongModel songModel(db);
    QCOMPARE(songModel.rowCount(), expectedSize);
}

void ProcessesTest::testSongProcessHandlesRemoveInvalidData() {
    constexpr int expectedSize = 1;

    std::unique_ptr<SongInsertProcess> songInsert(new SongInsertProcess(modelController, filesController, tmpSong));
    songInsert->start();

    SongModel songModel(db);
    QCOMPARE(songModel.rowCount(), expectedSize);

    QVariantList invalidData {
        10, false, "", QUrl("/foo/bar1")
    };

    for (const auto &data : qAsConst(invalidData)) {
        std::unique_ptr<SongRemoveProcess> songRemove(new SongRemoveProcess(modelController, filesController, data));
        songRemove->start();
    }

    songModel.select();
    QCOMPARE(songModel.rowCount(), expectedSize);
}

void ProcessesTest::testWallpaperProcessInsertAndRemoveData() {
    std::unique_ptr<WallpaperInsertProcess> wallpaperInsert(new WallpaperInsertProcess(modelController, filesController, tmpWallpaper));
    wallpaperInsert->start();

    WallpaperModel wallpaperModel(db);
    QCOMPARE(wallpaperModel.rowCount(), 1);
    QVERIFY(QFileInfo(expectedWallpaper.path()).exists());

    constexpr int expectedId = 1;
    QVariantMap wallpaperRemoveModelData {
        { "id",  expectedId },
        { "url", expectedWallpaper }
    };
    std::unique_ptr<WallpaperRemoveProcess> wallpaperRemove(new WallpaperRemoveProcess(modelController, filesController, wallpaperRemoveModelData));
    wallpaperRemove->start();

    wallpaperModel.select();

    QCOMPARE(wallpaperModel.rowCount(), 0);
    QVERIFY(!QFileInfo(expectedWallpaper.path()).exists());
}

void ProcessesTest::testWallpaperProcessHandlesInsertInvalidData() {
    constexpr int expectedSize = 0;
    constexpr int invalidData = 25;
    std::unique_ptr<WallpaperInsertProcess> wallpaperInsert(new WallpaperInsertProcess(modelController, filesController, invalidData));
    wallpaperInsert->start();

    WallpaperModel wallpaperModel(db);
    QCOMPARE(wallpaperModel.rowCount(), expectedSize);
}

void ProcessesTest::testWallpaperProcessHandlesRemoveInvalidData() {
    constexpr int expectedSize = 1;

    std::unique_ptr<WallpaperInsertProcess> wallpaperInsert(new WallpaperInsertProcess(modelController, filesController, tmpWallpaper));
    wallpaperInsert->start();

    WallpaperModel wallpaperModel(db);
    QCOMPARE(wallpaperModel.rowCount(), expectedSize);

    QVariantList invalidData {
        true,
        100,
        "",
        QUrl("/foo/bar")
    };

    for (const auto &data : qAsConst(invalidData)) {
        std::unique_ptr<WallpaperRemoveProcess> wallpaperRemove(new WallpaperRemoveProcess(modelController, filesController, data));
        wallpaperRemove->start();
    }

    wallpaperModel.select();
    QCOMPARE(wallpaperModel.rowCount(), expectedSize);
}

void ProcessesTest::testResumeUnfinishedPendingProcessResumeAndRunUnfinishedInsertProcesses() {
    QVariantList urls {
        tmpSong, tmpWallpaper
    };

    std::unique_ptr<PendingInsertProcess> pendingInsert(new PendingInsertProcess(modelController, urls));
    pendingInsert->start();

    PendingModel pendingModel(db);
    QCOMPARE(pendingModel.rowCount(), 2);

    std::unique_ptr<ResumeUnfinishedPendingProcess> resumeUnfinishedPending(new ResumeUnfinishedPendingProcess(modelController, filesController));
    resumeUnfinishedPending->start();

    pendingModel.select();
    QCOMPARE(pendingModel.rowCount(), 0);

    WallpaperModel wallpaperModel(db);
    SongModel songModel(db);

    QCOMPARE(wallpaperModel.rowCount(), 1);
    QVERIFY(QFileInfo(expectedWallpaper.path()).exists());

    QCOMPARE(songModel.rowCount(), 1);
    QVERIFY(QFileInfo(expectedSong.path()).exists());
}

void ProcessesTest::testRemoveMissingDataRemovesMissingData() {
    WallpaperModel wallpaperModel(db);

    QVector<QVariantMap> wallpaperData {
        {
            {"name", "wallpaper1"},
            {"url", "file:///foo/path/wallpaper1.jpeg"}
        },

        {
            {"name", "wallpaper2"},
            {"url", "file:///foo/path/wallpaper2.jpeg"}
        }
    };

    for (const auto &data : qAsConst(wallpaperData)) {
        wallpaperModel.append(data);
    }

    std::unique_ptr<WallpaperInsertProcess> wallpaperInsert(new WallpaperInsertProcess(modelController, filesController, tmpWallpaper));
    wallpaperInsert->start();

    wallpaperModel.select();
    QCOMPARE(wallpaperModel.rowCount(), 3);
    QVERIFY(QFileInfo(expectedWallpaper.path()).exists());

    SongModel songModel(db);

    QVector<QVariantMap> songData {
        {
            {"title", "song1"},
            {"url", "file:///foo/path/song1.mp3"},
            {"duration", 1000}
        },

        {
            {"title", "song2"},
            {"url", "file:///foo/path/song2.mp3"},
            {"duration", 1000}
        }
    };

    for (const auto &data : qAsConst(songData)) {
        songModel.append(data);
    }

    std::unique_ptr<SongInsertProcess> songInsert(new SongInsertProcess(modelController, filesController, tmpSong));
    songInsert->start();

    songModel.select();
    QCOMPARE(songModel.rowCount(), 3);
    QVERIFY(QFileInfo(expectedSong.path()).exists());

    std::unique_ptr<RemoveMissingDataProcess> missingRemove(new RemoveMissingDataProcess(modelController));
    missingRemove->start();

    wallpaperModel.select();
    songModel.select();

    QCOMPARE(wallpaperModel.rowCount(), 1);
    QVERIFY(QFileInfo(expectedWallpaper.path()).exists());

    QCOMPARE(songModel.rowCount(), 1);
    QVERIFY(QFileInfo(expectedSong.path()).exists());
}

QTEST_APPLESS_MAIN(ProcessesTest)

#include "tst_processestest.moc"
