#include <QtTest>
#include <QSignalSpy>

#include <QSqlDatabase>

#include <QDir>

#include <controllers/datacontroller.h>

class DataControllerTest : public QObject
{
    Q_OBJECT

public:
    DataControllerTest();
    ~DataControllerTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void cleanup();

    // TODO: Test Insert and Remove methods
    void testDataControllerContainsReturnTrueIfDataExistsAndFalseIfNot();

private:
    const QString corePath;
    const QString song;
};

DataControllerTest::DataControllerTest()
    : corePath(QDir::currentPath() + "/datacontrollertest"),
      song("song.mp3") {

}

DataControllerTest::~DataControllerTest() {

}

void DataControllerTest::initTestCase() {
    QFile songFile(song);
    QVERIFY(songFile.open(QIODevice::WriteOnly));
    songFile.write("010101010");
    songFile.close();
}

void DataControllerTest::cleanupTestCase() {
    QVERIFY(QFile::remove(song));
}

void DataControllerTest::cleanup() {
    QDir remover;

    remover.setPath(corePath);
    QVERIFY(remover.removeRecursively());
}

void DataControllerTest::testDataControllerContainsReturnTrueIfDataExistsAndFalseIfNot() {
    DataController dataController(corePath);
    QTest::qWait(50);

    QVariantList relationInsertModelData {
        QVariantMap {
            { "playlist", 1 },
            { "song", 1 }
        },

        QVariantMap {
            { "playlist", 1 },
            { "song", 2 }
        },

        QVariantMap {
            { "playlist", 2 },
            { "song", 3 }
        },
    };

    dataController.insertData(relationInsertModelData, Enums::Data::Relations);

    QTest::qWait(300);

    auto db = dataController.database();
    RelationModel relationModel(db);
    QCOMPARE(relationModel.rowCount(), 3);

    QVariantMap modelDataToFind {
        { "playlist", 1 },
        { "song", 2 }
    };

    QVERIFY(dataController.containsData(modelDataToFind, Enums::Data::Relations));

    QVariantMap modelDataWhichDoesntExists {
        { "playlist", 7 },
        { "song", 5 }
    };

    QVERIFY(!dataController.containsData(modelDataWhichDoesntExists, Enums::Data::Relations));
}

QTEST_APPLESS_MAIN(DataControllerTest)

#include "tst_datacontrollertest.moc"
