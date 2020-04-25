#include <QtTest>

#include <common/utility.h>
#include <common/enums.h>

class UtilityTest : public QObject {
    Q_OBJECT

public:
    UtilityTest();
    ~UtilityTest();

private slots:
    void testUtilityConvertsEnumToString();
    void testUtilityFormatsMsec();
    void testUtilityReadMsFromString();
    void testUtilityFormatFileSizeToHumanReadable();
};

UtilityTest::UtilityTest() {

}

UtilityTest::~UtilityTest() {

}

void UtilityTest::testUtilityConvertsEnumToString() {
    auto enumValue = Enums::Data::Songs;
    QCOMPARE(Utility::enumToString(enumValue), QStringLiteral("Songs"));
}

void UtilityTest::testUtilityFormatsMsec() {
    const int msec = 65000;
    QCOMPARE(Utility::formatTime(msec, "mm:ss"), QStringLiteral("01:05"));
}

void UtilityTest::testUtilityReadMsFromString() {
    const QString string = "1 m 24 s";

    const int ms = Utility::msFromString(string, "m 'm' s 's'");
    QCOMPARE(ms, 1 * 60 * 1000 + 24 * 1000);
}

void UtilityTest::testUtilityFormatFileSizeToHumanReadable() {
    QString tmpName = QStringLiteral("testFile.txt");
    QFile file(tmpName);
    QVERIFY(file.open(QIODevice::WriteOnly));
    file.write("10101");
    file.close();
    QCOMPARE(Utility::fileSize(tmpName), "5 bytes");
    QVERIFY(QFile::remove(tmpName));
}

QTEST_APPLESS_MAIN(UtilityTest)

#include "tst_utilitytest.moc"
