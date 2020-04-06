#include "sessioncontroller.h"

#include "../paths/paths.h"

#include <QFileInfo>
#include <QStandardPaths>
#include <QSettings>

Q_LOGGING_CATEGORY(sessionController, "session.controller")

namespace  {
    QString SESSION_FILENAME = QStringLiteral("session.ini");
}

SessionController::SessionController(QObject *parent)
    : QObject(parent),
      m_sessionLocation(paths::join(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation), SESSION_FILENAME)) {

    defaults();

    if (QFileInfo(m_sessionLocation).exists()) {
        qCInfo(sessionController) << "Restoring previous session";

        load();
    }
}

SessionController::SessionController(const QString &sessionLocation, QObject *parent)
    : QObject(parent),
      m_sessionLocation(paths::join(sessionLocation, SESSION_FILENAME)) {

    defaults();

    if (QFileInfo(m_sessionLocation).exists()) {
        qCInfo(sessionController) << "Restoring previous session";

        load();
    }
}

SessionController::~SessionController() {
    save();
}

void SessionController::save() {
    QSettings settings(m_sessionLocation, QSettings::IniFormat);
    settings.beginGroup("sessionManager");
    settings.setValue("cleanScreen", m_cleanScreen);
    settings.setValue("audioMuted", m_audioMuted);
    settings.setValue("playback", static_cast<int>(m_playback));
    settings.setValue("currentPlaylist", QVariant::fromValue(m_currentPlaylist));
    settings.setValue("currentSong", QVariant::fromValue(m_currentSong));
    settings.setValue("audioVolume", m_audioVolume);
    settings.setValue("currentPageIndex", m_currentPageIndex);
    settings.setValue("unfinishedPending", m_pending);
    settings.endGroup();
}

void SessionController::defaults() {
    m_cleanScreen = false;
    m_audioMuted = false;
    m_pending = false;
    m_playback = Playlist::Sequental;
    m_currentPlaylist = {-1, ""};
    m_currentSong = {-1, "", {-1, ""}};
    m_currentWallpaper = QUrl();
    m_audioVolume = 50;
    m_unfinishedPending = false;
    m_currentPageIndex = 0;
}

void SessionController::load() {
    QSettings settings(m_sessionLocation, QSettings::IniFormat);
    settings.beginGroup("sessionManager");
    setCleanScreen(settings.value("cleanScreen").toBool());
    setAudioMuted(settings.value("audioMuted").toBool());
    setPlayback(static_cast<Playlist::Playback>(settings.value("playback").toInt()));
    setCurrentPlaylist(settings.value("currentPlaylist").value<data::Playlist>());
    setCurrentSong(settings.value("currentSong").value<data::Song>());
    setAudioVolume(settings.value("audioVolume").toInt());
    setCurrentPageIndex(settings.value("currentPageIndex").toInt());
    setUnfinishedPending(settings.value("unfinishedPending").toBool());
    settings.endGroup();
}

QList<data::PageItem> SessionController::pages() const {
    return {
        {
            QUrl("qrc:/icons/gate"),
            QStringLiteral("Summary")
        },
        {
            QUrl("qrc:/icons/music"),
            QStringLiteral("Music")
        },
        {
            QUrl("qrc:/icons/playlist"),
            QStringLiteral("Playlists")
        },
        {
            QUrl("qrc:/icons/images"),
            QStringLiteral("Wallpapers")
        }
    };
}

bool SessionController::cleanScreen() const {
    return m_cleanScreen;
}

bool SessionController::audioMuted() const {
    return m_audioMuted;
}

bool SessionController::pending() const {
    return m_pending;
}

bool SessionController::unfinishedPending() const {
    return m_unfinishedPending;
}

Playlist::Playback SessionController::playback() const {
    return m_playback;
}

data::Playlist SessionController::currentPlaylist() const {
    return m_currentPlaylist;
}

data::Song SessionController::currentSong() const {
    return m_currentSong;
}

QUrl SessionController::currentWallpaper() const {
    return m_currentWallpaper;
}

int SessionController::audioVolume() const {
    return m_audioVolume;
}

int SessionController::currentPageIndex() const {
    return m_currentPageIndex;
}

void SessionController::setCleanScreen(const bool cleanScreen) {
    if (m_cleanScreen == cleanScreen) {
        return;
    }

    m_cleanScreen = cleanScreen;
    emit cleanScreenChanged(m_cleanScreen);
}

void SessionController::setAudioMuted(const bool audioMuted) {
    if (m_audioMuted == audioMuted) {
        return;
    }

    m_audioMuted = audioMuted;
    emit audioMutedChanged(m_audioMuted);
}

void SessionController::setPending(const bool pending) {
    if (m_pending == pending) {
        return;
    }

    m_pending = pending;
    emit pendingChanged(m_pending);
}

void SessionController::setUnfinishedPending(const bool unfinishedPending) {
    if (m_unfinishedPending == unfinishedPending) {
        return;
    }

    m_unfinishedPending = unfinishedPending;
    emit unfinishedPendingChanged(m_unfinishedPending);
}

void SessionController::setPlayback(const Playlist::Playback playback) {
    if (m_playback == playback) {
        return;
    }

    m_playback = playback;
    emit playbackChanged(m_playback);
}

void SessionController::setCurrentPlaylist(const data::Playlist &playlist) {
    if (m_currentPlaylist == playlist) {
        return;
    }

    m_currentPlaylist = playlist;
    emit currentPlaylistChanged(m_currentPlaylist);
}

void SessionController::setCurrentSong(const data::Song &song) {
    if (m_currentSong == song) {
        return;
    }

    m_currentSong = song;
    emit currentSongChanged(m_currentSong);
}

void SessionController::setCurrentWallpaper(const QUrl &url) {
    if (m_currentWallpaper == url) {
        return;
    }

    m_currentWallpaper = url;
    emit currentWallpaperChanged(m_currentWallpaper);
}

void SessionController::setAudioVolume(const int audioVolume) {
    if (m_audioVolume == audioVolume) {
        return;
    }

    m_audioVolume = audioVolume;
    emit audioVolumeChanged(m_audioVolume);
}

void SessionController::setCurrentPageIndex(const int currentIndex) {
    if (m_currentPageIndex == currentIndex) {
        return;
    }

    m_currentPageIndex = currentIndex;
    emit currentPageIndexChanged(m_currentPageIndex);
}
