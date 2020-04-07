#include <QtTest>
#include <QSignalSpy>

#include <QDir>
#include <QFile>

#include <vlc/vlc.h>
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

    void test_vlcParseLocal();
    void test_vlcParseRemote();

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
    QFile file(m_song.path());
    QVERIFY(file.open(QIODevice::WriteOnly));
    QVERIFY(file.write(":/song"));
}

void VlcMediaTest::cleanupTestCase() {
    QVERIFY(QFile::remove(m_song.path()));
}

void VlcMediaTest::test_vlcParseLocal() {
    vlc::VlcMedia vlcMedia(m_instance);
    vlcMedia = m_song;

    QSignalSpy spy(&vlcMedia, &vlc::VlcMedia::metaChanged);

    QTest::qWait(100);

    QVERIFY(vlcMedia.mediaType() == libvlc_media_type_t::libvlc_media_type_file);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(vlcMedia.meta().m_title, "song.mp3");
}

void VlcMediaTest::test_vlcParseRemote() {
    vlc::VlcMedia vlcMedia(m_instance);
    vlcMedia = QUrl("https://www.youtube.com/watch?v=QKUNo8MOzQA");

    QSignalSpy spy(&vlcMedia, &vlc::VlcMedia::metaChanged);

    QTest::qWait(1000);

    QVERIFY(vlcMedia.isParsed());
    QVERIFY(vlcMedia.mediaType() == libvlc_media_type_t::libvlc_media_type_stream);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(vlcMedia.meta().m_title, "Relaxing Sleep Music + Stress Relief - Relaxing Music, Insomnia, Meditation Music");
}

QTEST_APPLESS_MAIN(VlcMediaTest)

#include "tst_vlcmediatest.moc"
