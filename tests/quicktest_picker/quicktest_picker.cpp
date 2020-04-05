#include <QtQuickTest/quicktest.h>

#include <QQmlEngine>
#include <QQmlContext>

#include <tools/picker.h>

class Setup : public QObject {
    Q_OBJECT

public slots:
    void applicationAvailable() {
        qmlRegisterType<Picker>("com.gemini.tools", 0, 1, "Picker");
    }
};

QUICK_TEST_MAIN_WITH_SETUP(PickerQuickTest, Setup)

#include "quicktest_picker.moc"
