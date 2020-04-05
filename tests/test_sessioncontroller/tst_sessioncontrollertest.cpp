#include <QtTest>

#include <QDir>

#include <controllers/sessioncontroller.h>
#include <tools/playlist.h>
#include <data/playlistdata.h>
#include <data/songdata.h>

class SessionControllerTest : public QObject {
    Q_OBJECT

public:
    SessionControllerTest();
    ~SessionControllerTest();

private slots:
    void testSessionControllerLoadsWithDefaultsSettings();
    void testSessionControllerSavesAndLoadsSettings();
    void testSessionControllerSavesUnfinishedPendingWhenDestructorCalledWithPendingVariableSetToTrue();

    void initTestCase();

    void init();

private:
    const QString sessionFile;

};

SessionControllerTest::SessionControllerTest()
    : sessionFile(QDir::currentPath() + "/session.ini")
{

}

SessionControllerTest::~SessionControllerTest()
{

}

void SessionControllerTest::initTestCase() {
    qRegisterMetaTypeStreamOperators<data::Playlist>("data::Playlist");
    qRegisterMetaTypeStreamOperators<data::Song>("data::Song");
}

void SessionControllerTest::init() {
    if (QFileInfo(sessionFile).exists()) {
        QVERIFY(QFile::remove(sessionFile));
    }
}

void SessionControllerTest::testSessionControllerLoadsWithDefaultsSettings() {
    data::Playlist playlist{-1, ""};
    data::Song song{-1, "", playlist};

    {
        SessionController sessionContorller(QDir::currentPath());
        QCOMPARE(sessionContorller.cleanScreen(), false);
        QCOMPARE(sessionContorller.audioMuted(), false);
        QCOMPARE(sessionContorller.pending(), false);
        QCOMPARE(sessionContorller.playback(), Playlist::Sequental);
        QCOMPARE(sessionContorller.currentPlaylist(), playlist);
        QCOMPARE(sessionContorller.currentSong(), song);
        QCOMPARE(sessionContorller.currentWallpaper(), QUrl());
        QCOMPARE(sessionContorller.audioVolume(), 50);
        QCOMPARE(sessionContorller.currentPageIndex(), 0);
    }
}

void SessionControllerTest::testSessionControllerSavesAndLoadsSettings() {
    data::Playlist playlist{45, "Best"};
    data::Song song{25, "ok", playlist};

    {
        SessionController sessionController(QDir::currentPath());
        sessionController.setCleanScreen(true);
        sessionController.setAudioMuted(true);
        sessionController.setPlayback(Playlist::Loop);
        sessionController.setCurrentPlaylist(playlist);
        sessionController.setCurrentSong(song);
        sessionController.setAudioVolume(25);
        sessionController.setCurrentPageIndex(2);
    }

    {
        SessionController sessionController(QDir::currentPath());
        QCOMPARE(sessionController.cleanScreen(), true);
        QCOMPARE(sessionController.audioMuted(), true);
        QCOMPARE(sessionController.playback(), Playlist::Loop);
        QCOMPARE(sessionController.currentPlaylist(), playlist);
        QCOMPARE(sessionController.currentSong(), song);
        QCOMPARE(sessionController.audioVolume(), 25);
        QCOMPARE(sessionController.currentPageIndex(), 2);
    }
}

void SessionControllerTest::testSessionControllerSavesUnfinishedPendingWhenDestructorCalledWithPendingVariableSetToTrue() {
    {
        SessionController sessionController(QDir::currentPath());
        QCOMPARE(sessionController.unfinishedPending(), false);
        QCOMPARE(sessionController.pending(), false);
        sessionController.setPending(true);
    }

    {
        SessionController sessionController(QDir::currentPath());
        QCOMPARE(sessionController.unfinishedPending(), true);
    }
}

QTEST_APPLESS_MAIN(SessionControllerTest)

#include "tst_sessioncontrollertest.moc"
