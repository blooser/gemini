#ifndef SESSIONCONTROLLER_H
#define SESSIONCONTROLLER_H

#include "../data/playlistdata.h"
#include "../data/songdata.h"
#include "../data/pageitem.h"
#include "../common/deleters.h"
#include "../tools/playlist.h"

#include <QString>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(sessionController)

class SessionController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<data::PageItem> pages READ pages CONSTANT)
    Q_PROPERTY(bool cleanScreen READ cleanScreen
               WRITE setCleanScreen NOTIFY cleanScreenChanged)
    Q_PROPERTY(bool audioMuted READ audioMuted
               WRITE setAudioMuted NOTIFY audioMutedChanged)
    Q_PROPERTY(bool pending READ pending
               WRITE setPending NOTIFY pendingChanged)
    Q_PROPERTY(bool unfinishedPeding READ unfinishedPending
               WRITE setUnfinishedPending NOTIFY unfinishedPendingChanged)
    Q_PROPERTY(Playlist::Playback playback READ playback
               WRITE setPlayback NOTIFY playbackChanged)
    Q_PROPERTY(data::Playlist currentPlaylist READ currentPlaylist
               WRITE setCurrentPlaylist NOTIFY currentPlaylistChanged)
    Q_PROPERTY(data::Song currentSong READ currentSong
               WRITE setCurrentSong NOTIFY currentSongChanged)
    Q_PROPERTY(QUrl currentWallpaper READ currentWallpaper
               WRITE setCurrentWallpaper NOTIFY currentWallpaperChanged)
    Q_PROPERTY(int audioVolume READ audioVolume
               WRITE setAudioVolume NOTIFY audioVolumeChanged)
    Q_PROPERTY(int currentPageIndex READ currentPageIndex
               WRITE setCurrentPageIndex NOTIFY currentPageIndexChanged)

public:
    explicit SessionController(QObject *parent=nullptr);
    explicit SessionController(const QString &sessionLocation, QObject *parent=nullptr);
    ~SessionController();

    QList<data::PageItem> pages() const;

    bool cleanScreen() const;
    bool audioMuted() const;
    bool pending() const;
    bool unfinishedPending() const;
    Playlist::Playback playback() const;
    data::Playlist currentPlaylist() const;
    data::Song currentSong() const;
    QUrl currentWallpaper() const;
    int audioVolume() const;
    int currentPageIndex() const;

public slots:
    void setCleanScreen(const bool cleanScreen);
    void setAudioMuted(const bool audioMuted);
    void setPending(const bool pending);
    void setUnfinishedPending(const bool unfiniedPending);
    void setPlayback(const Playlist::Playback playback);
    void setCurrentPlaylist(const data::Playlist &playlist);
    void setCurrentSong(const data::Song &song);
    void setCurrentWallpaper(const QUrl &url);
    void setAudioVolume(const int audioVolume);
    void setCurrentPageIndex(const int currentIndex);

signals:
    void cleanScreenChanged(const bool cinemaMode);
    void audioMutedChanged(const bool audioMuted);
    void audioVolumeChanged(const int audioVolume);
    void pendingChanged(const bool pending);
    void unfinishedPendingChanged(const bool unfinishedPending);
    void playbackChanged(const Playlist::Playback playback);
    void currentPlaylistChanged(const data::Playlist &currentPlaylist);
    void currentSongChanged(const data::Song &song);
    void currentWallpaperChanged(const QUrl &wallpaper);
    void currentPageIndexChanged(const int index);

    // SwipeView
    void swipeLeft();
    void swipeRight();
    void swipe(const int index);

    // Playlist
    void selectPlaylist(const int id, Playlist::Selection selection=Playlist::Selection::SelectById);
    void selectSong(const int id, Playlist::Selection selection=Playlist::Selection::SelectById);
    void nextSong();
    void togglePlayer();
    void previousSong();
    void switchPlayback();

    // Player
    void switchAudioMute();

protected:
    void save();
    void load();
    void defaults();

private:
    const QString m_sessionLocation;
    int m_currentPageIndex;
    int m_audioVolume;
    bool m_cleanScreen;
    bool m_audioMuted;
    bool m_pending;
    bool m_unfinishedPending;
    Playlist::Playback m_playback;
    data::Playlist m_currentPlaylist;
    data::Song m_currentSong;
    QUrl m_currentWallpaper;
};

#endif // SESSIONCONTROLLER_H
