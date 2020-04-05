#include <QtTest>

#include <QHash>

#include "../gemini/src/helpers/pathhelper.h"

class PathHelperTest : public QObject {
    Q_OBJECT

public:
    PathHelperTest();

private slots:
    void join_1_test();
    void join_2_test();
    void join_3_test();

private:
    const QString rootPath;
};

PathHelperTest::PathHelperTest()
    : rootPath("gemini") {
}

void PathHelperTest::join_1_test() {
    QString path = PathHelper::join(rootPath, "foo");
    QVERIFY(path == "gemini/foo");
}

void PathHelperTest::join_2_test() {
    QString path = PathHelper::join(rootPath, "foo", "bar");
    QVERIFY(path == "gemini/foo/bar");
}

void PathHelperTest::join_3_test() {
    QString path = PathHelper::join(rootPath, "foo", "bar", "tst");
    QVERIFY(path == "gemini/foo/bar/tst");
}

QTEST_APPLESS_MAIN(PathHelperTest)

#include "tst_pathhelper.moc"
