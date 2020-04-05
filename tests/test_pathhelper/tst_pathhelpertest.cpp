#include <QtTest>

#include <helpers/pathhelper.h>

class PathHelperTest : public QObject {
    Q_OBJECT

public:
    PathHelperTest();
    ~PathHelperTest();

private slots:
    void testPathHelperJoinValidPath();
};

PathHelperTest::PathHelperTest() {

}

PathHelperTest::~PathHelperTest() {

}

void PathHelperTest::testPathHelperJoinValidPath() {
    QString joinResult = PathHelper::join("/foo/bar", "tst1", "tst2", "tst3", "tst4", "tst5");
    QCOMPARE(joinResult, QStringLiteral("/foo/bar/tst1/tst2/tst3/tst4/tst5"));

    QString joinBenchmark;
    QBENCHMARK {
        joinBenchmark = PathHelper::join("/foo/bar", "tst1", "tst2", "tst3",
                                         "tst4", "tst5", "tst6", "tst7");
    }
    Q_UNUSED(joinBenchmark);
}

QTEST_APPLESS_MAIN(PathHelperTest)

#include "tst_pathhelpertest.moc"
