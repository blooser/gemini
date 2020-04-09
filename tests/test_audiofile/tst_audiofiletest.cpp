#include <QtTest>
#include <QSignalSpy>

#include <QDir>
#include <QFile>

#include <audio/audiofile.h>

class AudioFileTest : public QObject
{
    Q_OBJECT

public:
    AudioFileTest();
    ~AudioFileTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_audioFileReadsTags();

private:
    QUrl m_song;
};

AudioFileTest::AudioFileTest()
    : m_song(QUrl::fromLocalFile(QDir::currentPath()  + "/song.mp3"))
{

}

AudioFileTest::~AudioFileTest()
{

}

void AudioFileTest::initTestCase() {
    QFile songFile(":/song");
    QVERIFY(songFile.open(QIODevice::ReadOnly));

    QFile file(m_song.path());
    QVERIFY(file.open(QIODevice::WriteOnly));
    QVERIFY(file.write(songFile.readAll()));
    songFile.close();
    file.close();
    QVERIFY(QFileInfo(m_song.path()).exists());
}

void AudioFileTest::cleanupTestCase() {
    QVERIFY(QFile::remove(m_song.path()));
}

void AudioFileTest::test_audioFileReadsTags() {
    AudioFile audioFile(m_song);

    // These values are in meta info of song.mp3 (check testingresources/song.mp3)
    QCOMPARE(audioFile.duration(), 261);
    QCOMPARE(audioFile.title(), "TestSong");
    QCOMPARE(audioFile.artist(), "Test");
    QCOMPARE(audioFile.album(), "testing");
    QCOMPARE(audioFile.genre(), "Dream");
}

QTEST_APPLESS_MAIN(AudioFileTest)

#include "tst_audiofiletest.moc"
