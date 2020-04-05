#include <QtTest>

#include <QtSql/QSqlDatabase>

#include <database/databasecore.h>
#include <database/databasetables.h>

class DatabaseTest : public QObject {
    Q_OBJECT

public:
    DatabaseTest();
    ~DatabaseTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testDatabaseCreatesTables();
    void testDatabaseRunQuery();
    void testDatabaseReturnError();

private:
    QSqlDatabase db;
};

DatabaseTest::DatabaseTest() {

}

DatabaseTest::~DatabaseTest()
{

}

void DatabaseTest::initTestCase() {
    database::core::setup(db, "", ":memory:");
    QVERIFY(db.isValid());
}

void DatabaseTest::cleanupTestCase() {

}

void DatabaseTest::init() {
    db.open();
    QVERIFY(db.isOpen());
}

void DatabaseTest::cleanup() {
    db.close();
    QVERIFY(!db.isOpen());
}

void DatabaseTest::testDatabaseCreatesTables() {
    QVERIFY(db.tables().isEmpty());

    for (const auto &table : database::Tables) {
        table(db);
    }

    QVERIFY(!db.tables().isEmpty());

    QStringList expectedTables {
        "wallpapers", "playlists", "songs", "relations", "pending"
    };

    for (const auto &table : qAsConst(expectedTables)) {
        db.tables().contains(table);
    }
}

void DatabaseTest::testDatabaseRunQuery() {
    QString queryMsg = QStringLiteral("CREATE TABLE testtable('id' INTEGER NOT NULL)");
    QSqlQuery query(db);
    query.prepare(queryMsg);

    database::core::run(query);

    QVERIFY(db.tables().contains("testtable"));
}

void DatabaseTest::testDatabaseReturnError() {
    QString corruptQueryMsg = QStringLiteral("INSERT INTO nonexiststabtle(id, name) VALUES(1, 'test')");
    QSqlQuery query(db);
    query.prepare(corruptQueryMsg);

    database::core::run(query);
    QVERIFY(database::core::error(query));
}

QTEST_APPLESS_MAIN(DatabaseTest)

#include "tst_databasetest.moc"
