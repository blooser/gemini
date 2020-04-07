#include <QtTest>
#include <QSignalSpy>

#include <QDir>
#include <QFile>

#include <vlc/vlc.h>

// These comes from gemini
#include <vlc/vlcmedia.h>
#include <vlc/vlcmeta.h>

class VlcMediaTest : public QObject
{
    Q_OBJECT

public:
    VlcMediaTest();
    ~VlcMediaTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_vlcParseFile();

private:
    QUrl m_song;
    libvlc_instance_t *m_instance;
};

VlcMediaTest::VlcMediaTest()
    : m_song(QUrl::fromLocalFile(QDir::currentPath()  + "/song.mp3"))
{
    m_instance = libvlc_new(0, nullptr);
}

VlcMediaTest::~VlcMediaTest()
{
    libvlc_release(m_instance);
}

void VlcMediaTest::initTestCase() {
    QFile songFile(":/song");
    QVERIFY(songFile.open(QIODevice::ReadOnly));

    QFile file(m_song.path());
    QVERIFY(file.open(QIODevice::WriteOnly));
    QVERIFY(file.write(songFile.readAll()));
    songFile.close();
    file.close();
    QVERIFY(QFileInfo(m_song.path()).exists());
}

void VlcMediaTest::cleanupTestCase() {
    QVERIFY(QFile::remove(m_song.path()));
}

void VlcMediaTest::test_vlcParseFile() {
    vlc::VlcMedia vlcMedia(m_instance);
    vlcMedia = m_song;

    QSignalSpy spy(&vlcMedia, &vlc::VlcMedia::metaChanged);

    QTest::qWait(150);

    QCOMPARE(spy.count(), 1);
    QVERIFY(vlcMedia.isParsed());
    QCOMPARE(vlcMedia.duration(), 261941);
    // These values are in meta info of song.mp3 (check testingresources directory)
    QCOMPARE(vlcMedia.meta().m_title, "TestSong");
    QCOMPARE(vlcMedia.meta().m_artist, "Test");
    QCOMPARE(vlcMedia.meta().m_album, "testing");
    QCOMPARE(vlcMedia.meta().m_genre, "Dream");
}

QTEST_APPLESS_MAIN(VlcMediaTest)

#include "tst_vlcmediatest.moc"
