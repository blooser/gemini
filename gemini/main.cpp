#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMetaObject>
#include <QFontDatabase>

#include "controllers/objectcontroller.h"
#include "controllers/sessioncontroller.h"
#include "controllers/datacontroller.h"

#include "tools/picker.h"
#include "tools/player.h"
#include "tools/circleprogressbar.h"
#include "tools/playlist.h"

#include "common/enums.h"
#include "common/utility.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    app.setApplicationName(ProjectName);
    app.setApplicationVersion(ProjectVersion);
    app.setOrganizationName(OrganizationName);
    app.setOrganizationDomain(OrganizationDomain);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/arbutus");
    app.setFont(QFont(QFontDatabase::applicationFontFamilies(fontId).at(0)));

    qmlRegisterUncreatableMetaObject(Enums::staticMetaObject, "com.gemini.enums", 0, 1, "Enums", "Could not create enums!");
    qRegisterMetaType<Enums::Data>("Enums::Data");
    qRegisterMetaType<Enums::Dialog>("Enums::Dialog");

    qRegisterMetaTypeStreamOperators<data::Playlist>("data::Playlist");
    qRegisterMetaTypeStreamOperators<data::Song>("data::Song");

    qmlRegisterSingletonType(QUrl(QStringLiteral("qrc:///helper/Helper.qml")), "com.gemini.helper", 0, 1, "Helper");
    qmlRegisterSingletonType(QUrl(QStringLiteral("qrc:///GeminiStyles.qml")), "com.gemini.styles", 0, 1, "GeminiStyles");

    qmlRegisterSingletonType<Utility>("com.gemini.common", 0, 1, "Utility", [](QQmlEngine *, QJSEngine*) -> QObject* {
        QQmlEngine::setObjectOwnership(&Utility::instance(), QQmlEngine::CppOwnership);
        return &Utility::instance();
    });

    qmlRegisterType<Picker>("com.gemini.tools", 0, 1, "Picker");
    qmlRegisterType<Player>("com.gemini.tools", 0, 1, "Player");
    qmlRegisterType<CircleProgressBar>("com.gemini.tools", 0, 1, "CircleProgressBar");
    qmlRegisterType<Playlist>("com.gemini.tools", 0, 1, "Playlist");

    ObjectController m_objectController;
    SessionController m_sessionController;
    DataController m_dataController;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("objectController", &m_objectController);
    engine.rootContext()->setContextProperty("sessionController", &m_sessionController);
    engine.rootContext()->setContextProperty("dataController", &m_dataController);

    m_dataController.setQMLContext(engine);

    const QUrl url(QStringLiteral("qrc:///main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
