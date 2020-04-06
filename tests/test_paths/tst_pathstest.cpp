#include <QtTest>
#include <QUrl>

#include <paths/paths.h>

class PathsTest : public QObject {
    Q_OBJECT

public:
    PathsTest();
    ~PathsTest();

private slots:
    void testPathsJoinPaths();
    void testPathsTellIsAudio();
    void testPathsTellIsImage();
    void testPathsTellIsLocal();
    void testPathsTellIsRemote();
    void testPathsReturnValidPath();
};

PathsTest::PathsTest() {

}

PathsTest::~PathsTest() {

}

void PathsTest::testPathsJoinPaths() {
    QString joinResult = paths::join("/foo/bar", "tst1", "tst2", "tst3", "tst4", "tst5");
    QCOMPARE(joinResult, QStringLiteral("/foo/bar/tst1/tst2/tst3/tst4/tst5"));

    QString joinBenchmark;
    QBENCHMARK {
        joinBenchmark = paths::join("/foo/bar", "tst1", "tst2", "tst3",
                                         "tst4", "tst5", "tst6", "tst7");
    }
    Q_UNUSED(joinBenchmark);
}

void PathsTest::testPathsTellIsAudio() {
    auto audio = QUrl::fromLocalFile("/foo/bar/path/audio.mp3");
    auto notAudio = QUrl::fromLocalFile("/foo/bar/path/audio.txt");

    QVERIFY(paths::isAudio(audio));
    QVERIFY(not paths::isAudio(notAudio));
}

void PathsTest::testPathsTellIsImage() {
    auto image = QUrl::fromLocalFile("/foo/bar/path/image.jpeg");
    auto notImage = QUrl::fromLocalFile("/foo/bar/path/image.cpp");

    QVERIFY(paths::isImage(image));
    QVERIFY(not paths::isImage(notImage));
}

void PathsTest::testPathsTellIsLocal() {
    auto local = QUrl::fromLocalFile("/foo/bar/path/file");
    auto remote = QUrl("https://www.qt.io/");

    QVERIFY(paths::isLocal(local));
    QVERIFY(not paths::isLocal(remote));

}

void PathsTest::testPathsTellIsRemote() {
    auto local = QUrl::fromLocalFile("/foo/bar/path/file");
    auto remote = QUrl("https://www.qt.io/");

    QVERIFY(paths::isRemote(remote));
    QVERIFY(not paths::isRemote(local));
}

void PathsTest::testPathsReturnValidPath() {
    auto local = QUrl::fromLocalFile("/foo/bar/path/file");
    auto remote = QUrl("https://www.qt.io/");
    auto unknown = QUrl("010101010010101");

    QVERIFY(paths::getPath(local) == paths::Path::Local);
    QVERIFY(paths::getPath(remote) == paths::Path::Remote);
    QVERIFY(paths::getPath(unknown) == paths::Path::Unknown);
}

QTEST_APPLESS_MAIN(PathsTest)

#include "tst_pathstest.moc"
