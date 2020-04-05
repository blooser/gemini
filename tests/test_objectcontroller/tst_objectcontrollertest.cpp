#include <QtTest>
#include <QSignalSpy>

#include <common/enums.h>
#include <controllers/objectcontroller.h>

class ObjectControllerTest : public QObject
{
    Q_OBJECT

public:
    ObjectControllerTest();
    ~ObjectControllerTest();

private slots:
    void testObjectControllerCreatesValidDialogPath();

};

ObjectControllerTest::ObjectControllerTest()
{

}

ObjectControllerTest::~ObjectControllerTest()
{

}

void ObjectControllerTest::testObjectControllerCreatesValidDialogPath() {
    ObjectController objectController;
    QSignalSpy spy(&objectController, &ObjectController::open);

    objectController.openDialog(Enums::Dialog::ConfirmDialog, {}, QVariant());

    QCOMPARE(spy.count(), 1);
    auto arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).toString(), QStringLiteral("qrc:/dialogs/ConfirmDialog.qml"));
}

QTEST_APPLESS_MAIN(ObjectControllerTest)

#include "tst_objectcontrollertest.moc"
