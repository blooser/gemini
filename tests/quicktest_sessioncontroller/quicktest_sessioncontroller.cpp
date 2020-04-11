#include <QtQuickTest>

#include <QQmlEngine>
#include <QQmlContext>

#include <controllers/sessioncontroller.h>
#include <tools/playlist.h>
#include <data/songdata.h>
#include <data/playlistdata.h>

class Setup : public QObject {
    Q_OBJECT

public:
    Setup()
        : playlist{5, "playlist"},
          song{25, "", 0, "", "", "", "", false, QString("/foo/bar/song.mp3"), playlist} {}

public slots:
    void applicationAvailable() {
        qmlRegisterType<Playlist>("com.gemini.tools", 0, 1, "Playlist");
    }

    void qmlEngineAvailable(QQmlEngine *engine) {
        engine->rootContext()->setContextProperty("sessionController", &sessionController);
        engine->rootContext()->setContextProperty("playlist", QVariant::fromValue(playlist));
        engine->rootContext()->setContextProperty("song", QVariant::fromValue(song));
    }

private:
    SessionController sessionController;
    data::Playlist playlist;
    data::Song song;
};

QUICK_TEST_MAIN_WITH_SETUP(SessionControllerQuickTest, Setup)

#include "quicktest_sessioncontroller.moc"
