#include <QtTest>

#include <QDir>

#include <common/enums.h>
#include <controllers/filescontroller.h>

class FileControllerTest : public QObject {
    Q_OBJECT

public:
    FileControllerTest();
    ~FileControllerTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testFilesControllerGeneratesValidUrl();
    void testFilesControllerPutsFilesIntoValidPathAndRemovesFile();

private:
    const QUrl path;
    const QUrl testFilePath;
    const QUrl expectedNewUrl;
    FilesController filesController;
};

FileControllerTest::FileControllerTest()
    : path(QUrl::fromLocalFile(QDir::currentPath())),
      testFilePath(QUrl::fromLocalFile(path.path() + "/test_file.jpeg")),
      expectedNewUrl(QUrl::fromLocalFile(path.path() + "/wallpapers/test_file.jpeg")),
      filesController(path.path()) {

}

FileControllerTest::~FileControllerTest() {

}

void FileControllerTest::initTestCase() {
    QDir dirChecker(path.path());
    auto dirs = dirChecker.entryList(QDir::Dirs);
    QVERIFY(dirs.contains("wallpapers"));
    QVERIFY(dirs.contains("songs"));

    QFile file(testFilePath.path());
    QVERIFY(file.open(QIODevice::WriteOnly));
    file.write(QByteArray("010101010110101"));
    file.close();
}

void FileControllerTest::cleanupTestCase() {
    QVERIFY(QFile::remove(testFilePath.path()));
    QDir remover;
    remover.setFilter(QDir::Dirs);
    for (const auto &subdir : filesController.subdirectories()) {
        remover.setPath(path.path() + "/" + subdir);
        QVERIFY(remover.removeRecursively());
    }
}

void FileControllerTest::testFilesControllerGeneratesValidUrl() {
    const QUrl tempUrl = QUrl::fromLocalFile("/foo/bar/test/song.mp3");
    const QUrl expectedUrl = QUrl::fromLocalFile(path.path() + "/songs/song.mp3");
    auto generatedUrl = filesController.generateUrl(tempUrl, Enums::Data::Songs);
    QCOMPARE(generatedUrl, expectedUrl);
}

void FileControllerTest::testFilesControllerPutsFilesIntoValidPathAndRemovesFile() {
    auto newUrl = filesController.put(testFilePath, Enums::Data::Wallpapers);
    QVERIFY(!newUrl.isEmpty());
    QCOMPARE(newUrl, expectedNewUrl);
    QVERIFY(QFileInfo(newUrl.path()).exists());

    filesController.remove(expectedNewUrl);
    QVERIFY(!QFileInfo(expectedNewUrl.path()).exists());
}

QTEST_APPLESS_MAIN(FileControllerTest)

#include "tst_filecontrollertest.moc"
