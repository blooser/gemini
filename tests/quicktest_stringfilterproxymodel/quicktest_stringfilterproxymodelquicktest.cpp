#include <QtQuickTest>

#include <QQmlEngine>
#include <QQmlContext>

#include <tools/stringfilterproxymodel.h>

class Setup : public QObject {
    Q_OBJECT

public:
    Setup() {}

public slots:
    void applicationAvailable() {
        qmlRegisterType<StringFilterProxyModel>("com.gemini.tools", 0, 1, "StringFilterProxyModel");
    }
};

QUICK_TEST_MAIN_WITH_SETUP(StringFilterProxyModelQuickTest, Setup)

#include "quicktest_stringfilterproxymodelquicktest.moc"
