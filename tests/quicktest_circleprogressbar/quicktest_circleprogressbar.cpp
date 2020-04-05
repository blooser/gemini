#include <QtQuickTest/quicktest.h>

#include <QQmlEngine>
#include <QQmlContext>

#include <tools/circleprogressbar.h>

class Setup : public QObject {
    Q_OBJECT

public:
    Setup() {}

public slots:
    void applicationAvailable() {
        qmlRegisterType<CircleProgressBar>("com.gemini.tools", 0, 1, "CircleProgressBar");
    }
};

QUICK_TEST_MAIN_WITH_SETUP(CircleProgressBarQuickTest, Setup)

#include "quicktest_circleprogressbar.moc"
