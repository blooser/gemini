#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "../data/playlistdata.h"
#include "../data/songdata.h"

#include <QAbstractItemModel>
#include <QQmlParserStatus>
#include <QAbstractListModel>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(playlistTool)

class Playlist : public QObject,
                 public QQmlParserStatus {
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(Playback playback MEMBER m_playback NOTIFY playbackChanged)
    Q_PROPERTY(data::Playlist playlist READ playlist NOTIFY playlistChanged)
    Q_PROPERTY(data::Song currentSong READ currentSong NOTIFY currentSongChanged)
    Q_PROPERTY(QAbstractItemModel* playlists READ playlists
               WRITE setPlaylists NOTIFY playlistsChanged)
    Q_PROPERTY(QAbstractItemModel* songs READ songs
               WRITE setSongs NOTIFY songsChanged)

public:
    enum Playback {
        Sequental,
        Loop,
        Random,
    };
    Q_ENUM(Playback)

    enum Selection {
        SelectByIndex,
        SelectById
    };
    Q_ENUM(Selection)

    explicit Playlist(QObject *parent = nullptr);

    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();
    Q_INVOKABLE void selectPlaylist(const int data, const Selection=SelectById);
    Q_INVOKABLE void selectSong(const int data, const Selection=SelectById);
    Q_INVOKABLE void switchPlayback();

    int currentIndex() const;
    data::Playlist playlist() const;
    data::Song currentSong() const;

    QAbstractItemModel *playlists() const;
    void setPlaylists(QAbstractItemModel *playlists);

    QAbstractItemModel *songs() const;
    void setSongs(QAbstractItemModel *songs);

    // QQmlParserStatus
    void classBegin() override;
    void componentComplete() override;

private slots:
    void selectFirstPlaylistIfThereIsOnlyOnePlaylist();
    void invalidePlaylistIfThereIsNotPlaylist();
    void updateSongsSize();
    void updateCurrentSong();

    void observePlaylists();
    void observeSongs();

signals:
    void playlistChanged(const data::Playlist &playlist);
    void currentIndexChanged(const int currentIndex);
    void currentSongChanged(const data::Song currentSong);
    void playbackChanged(const Playback playback);
    void playlistsChanged(const QAbstractItemModel *playlists);
    void songsChanged(const QAbstractItemModel *songs);

protected:
    void random();
    void loop(bool reversed=false);
    void sequental(bool reversed=false);

private:
    int m_songsSize;
    int m_currentIndex;
    data::Playlist m_playlist;
    data::Song m_currentSong;
    Playback m_playback;
    QAbstractItemModel *m_playlists;
    QAbstractItemModel *m_songs;

    QVariant getSongData(const int row, const QByteArray &data) const;
    QVariant getPlaylistData(const int row, const QByteArray &data) const;
    QVariant getData(QAbstractItemModel *model, const int row, const QByteArray &data) const;
    int findRowWithId(QAbstractItemModel *model, const QVariant &id);

    void setPlaylist(const int row);
    void setCurrentSong(const int row);

    void observe();
    void setupConnections();
};

#endif // PLAYLIST_H
