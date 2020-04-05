#include <QtTest>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMetaEnum>

#include <memory>

#include "../gemini/src/database/databasetables.h"
#include "../gemini/src/controllers/filescontroller.h"
#include "../gemini/src/helpers/pathhelper.h"


class GeminiTest : public QObject {
    Q_OBJECT

public:
    GeminiTest();
    ~GeminiTest();

private slots:
    void initTestCase();

    // Data base
    void type_test();
    void setup_test();
    void database_test();
    void run_test();

    // Controllers
    void data_controller_test();

    // Path Helper
    void join_test();

    void cleanupTestCase();

private:
    const QString testPath;
    const QString dbPath;
    const QString connection;
    const QString rootPath;
    QSqlDatabase db;
    FilesController dbController;
};

GeminiTest::GeminiTest()
    : testPath(QDir::currentPath()),
      dbPath(testPath + "/" + "local_test.db"),
      connection("gemini_test"),
      rootPath("gemini"),
      dbController(testPath) {
}

GeminiTest::~GeminiTest() {

}

void GeminiTest::initTestCase() {

}

void GeminiTest::type_test() {
    QVERIFY(database::core::DB_TYPE == "QSQLITE");
}

void GeminiTest::setup_test() {
    database::core::setup(db, dbPath, connection);
    QVERIFY(db.isOpen());
    QVERIFY(QFileInfo(dbPath).exists());
}

void GeminiTest::database_test() {
    auto t_db = database::core::database(connection);
    QVERIFY(db.databaseName() == t_db.databaseName());
}

void GeminiTest::run_test() {
    for (const auto &table : database::Tables) {
        table(db);
    }

    auto tables = db.tables();
    QVERIFY(tables.contains("wallpapers"));
    QVERIFY(tables.contains("playlists"));
    QVERIFY(tables.contains("songs"));
}

void GeminiTest::data_controller_test() {
    QVERIFY(dbController.path() == testPath);
    for (const auto &subdir : dbController.subdirectories()) {
        QVERIFY(QFileInfo(testPath + "/" + subdir).exists());
    }

    QString tmpPath = testPath + "/" + "tmp_gemini_test_file.txt";
    QFile file(tmpPath);
    QVERIFY(file.open(QIODevice::WriteOnly));
    file.write(QByteArray("gemini_test"));
    file.close();

    QString newPath = dbController.put(tmpPath, Enums::Data::Wallpapers);
    QVERIFY(!newPath.isEmpty());
    QVERIFY(QFileInfo(newPath).exists());
    dbController.remove(newPath);
    QVERIFY(!QFileInfo(newPath).exists());
}

void GeminiTest::join_test() {
    QString path = PathHelper::join(rootPath, "foo", "bar", "tst");
    QVERIFY(path == "gemini/foo/bar/tst");

    QString finalPath;
    QBENCHMARK {
        finalPath = PathHelper::join(rootPath, "foo", "bar",
                                               "tst", "gemini",
                                               "space", "rocket");
    }
    Q_UNUSED(finalPath);
}

void GeminiTest::cleanupTestCase() {
    QVERIFY(QFile::remove(dbPath));
    for (const auto &subdir : dbController.subdirectories()) {
        QVERIFY(QDir(dbController.path() + "/" + subdir).removeRecursively());
    }
}

QTEST_APPLESS_MAIN(GeminiTest)

#include "tst_gemini.moc"
