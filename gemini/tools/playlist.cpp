#include "playlist.h"

#include <QRandomGenerator>

#define INVALID -1
#define INVALID_PLAYLIST \
    data::Playlist {-1, ""}
#define INVALID_SONG \
    data::Song {-1, "", INVALID_PLAYLIST}

Q_LOGGING_CATEGORY(playlistTool, "playlist")

Playlist::Playlist(QObject *parent)
    : QObject(parent),
      m_songsSize(INVALID),
      m_currentIndex(INVALID),
      m_playlist(INVALID_PLAYLIST),
      m_currentSong(INVALID_SONG),
      m_playback(Playback::Sequental),
      m_playlists(nullptr),
      m_songs(nullptr)
{
    setupConnections();
}

int Playlist::currentIndex() const {
    return m_currentIndex;
}

data::Playlist Playlist::playlist() const {
    return m_playlist;
}

data::Song Playlist::currentSong() const {
    return m_currentSong;
}

QAbstractItemModel* Playlist::playlists() const {
    return m_playlists;
}

QAbstractItemModel* Playlist::songs() const {
    return m_songs;
}

QVariant Playlist::getSongData(const int row, const QByteArray &data) const {
    return getData(m_songs, row, data);
}

QVariant Playlist::getPlaylistData(const int row, const QByteArray &data) const {
    return getData(m_playlists, row, data);
}

QVariant Playlist::getData(QAbstractItemModel *model, const int row, const QByteArray &data) const {
    if (not model) {
        return QVariant();
    }

    auto index = model->index(row, 0);
    auto role = model->roleNames().key(data);
    return model->data(index, role);
}

void Playlist::next() {
    switch (m_playback) {
        case Playlist::Playback::Sequental:
            sequental();
            break;
        case Playlist::Playback::Loop:
            loop();
            break;
        case Playlist::Playback::Random:
            random();
            break;
    }
}

void Playlist::previous() {
    switch (m_playback) {
        case Playlist::Playback::Sequental:
            sequental(true);
            break;
        case Playlist::Playback::Loop:
            loop(true);
            break;
        case Playlist::Playback::Random:
            random();
            break;
    }
}

void Playlist::setPlaylist(const int row) {
    if (row == INVALID) {
        m_playlist = INVALID_PLAYLIST;
        emit playlistChanged(m_playlist);
        return;
    }

    m_playlist = data::Playlist {
        getPlaylistData(row, "id").toInt(),
        getPlaylistData(row, "name").toString()
    };

    emit playlistChanged(m_playlist);
}

void Playlist::setCurrentSong(const int row) {
    if (row == INVALID or m_playlist == INVALID_PLAYLIST) {
        m_currentSong = INVALID_SONG;
        qDebug() << m_currentSong.m_id << m_currentSong.m_url;
        emit currentSongChanged(m_currentSong);
        return;
    }

    m_currentSong = data::Song {
        getSongData(row, "id").toInt(),
        getSongData(row, "url").toString(),
        m_playlist
    };

    emit currentSongChanged(m_currentSong);
}

int Playlist::findRowWithId(QAbstractItemModel *model, const QVariant &id) {
    QModelIndex index;
    int role = model->roleNames().key("id");
    for (int i=0; i<model->rowCount(); ++i) {
        index = model->index(i, 0);

        if (model->data(index, role).toInt() == id) {
            return i;
        }
    }

    return -1;
}

void Playlist::selectPlaylist(const int data, const Selection selection) {
    if (not m_playlists) {
        return;
    }

    switch (selection) {
        case SelectById:
            setPlaylist(findRowWithId(m_playlists, data));
            break;

        case SelectByIndex:
            setPlaylist(data);
            break;
    }
}

void Playlist::selectSong(const int data, const Selection selection) {
    if (!m_songs or m_songsSize <= 0) {
        return;
    }

    switch (selection) {
        case SelectById:
            m_currentIndex = findRowWithId(m_songs, data);
            break;
        case SelectByIndex:
            m_currentIndex = data;
            break;
    }

    emit currentIndexChanged(m_currentIndex);
}

void Playlist::switchPlayback() {
    m_playback = static_cast<Playback>(m_playback + 1 > Playback::Random ? Playback::Sequental : m_playback + 1);
    emit playbackChanged(m_playback);
}

void Playlist::sequental(bool reversed) {
    if (not reversed) {
        if (m_currentIndex + 1 < m_songsSize) {
            ++m_currentIndex;
        }
    } else {
        if (m_currentIndex - 1 >= 0) {
            --m_currentIndex;
        }
    }

    emit currentIndexChanged(m_currentIndex);
}

void Playlist::loop(bool reversed) {
    if (not reversed) {
        m_currentIndex = (m_currentIndex + 1 < m_songsSize) ? m_currentIndex + 1 : 0;
    } else {
        m_currentIndex = (m_currentIndex - 1 >= 0) ? m_currentIndex - 1 : m_songsSize - 1;
    }

    emit currentIndexChanged(m_currentIndex);
}

void Playlist::random() {
    m_currentIndex = QRandomGenerator::system()->bounded(m_songsSize);
    emit currentIndexChanged(m_currentIndex);
}

void Playlist::updateSongsSize() {
    m_songsSize = m_songs->rowCount();
}

void Playlist::selectFirstPlaylistIfThereIsOnlyOnePlaylist() {
    if (m_playlists and m_playlists->rowCount() == 1) {
        setPlaylist(0);
    }
}

void Playlist::invalidePlaylistIfThereIsNotPlaylist() {
    if (m_playlists and m_playlists->rowCount() == 0) {
        m_playlist = INVALID_PLAYLIST;
        emit playlistChanged(m_playlist);

        m_currentIndex = INVALID;
        emit currentIndexChanged(m_currentIndex);
    }
}

void Playlist::observePlaylists() {
    connect(m_playlists, &QAbstractItemModel::rowsRemoved,
            this, &Playlist::invalidePlaylistIfThereIsNotPlaylist);
    connect(m_playlists, &QAbstractItemModel::rowsInserted,
            this, &Playlist::selectFirstPlaylistIfThereIsOnlyOnePlaylist);
}

void Playlist::observeSongs() {
    connect(m_songs, &QAbstractItemModel::modelReset,
            this, &Playlist::updateSongsSize);
    connect(m_songs, &QAbstractItemModel::rowsInserted,
            this, &Playlist::updateSongsSize);
    connect(m_songs, &QAbstractItemModel::rowsRemoved,
            this, &Playlist::updateSongsSize);
}

void Playlist::setPlaylists(QAbstractItemModel *playlists) {
    if (not playlists) {
        qCWarning(playlistTool) << "Can't set empty playlists!";
        return;
    }

    m_playlists = playlists;
    emit playlistsChanged(m_playlists);
}

void Playlist::setSongs(QAbstractItemModel *songs) {
    if (not songs) {
        qCWarning(playlistTool) << "Can't set empty songs!";
        return;
    }

    m_songs = songs;
    emit songsChanged(m_songs);

    m_currentIndex = INVALID;

    updateSongsSize();
}

void Playlist::updateCurrentSong() {
    setCurrentSong(m_currentIndex);
}

void Playlist::setupConnections() {
    connect(this, &Playlist::currentIndexChanged,
            this, &Playlist::updateCurrentSong);
    connect(this, &Playlist::playlistsChanged,
            this, &Playlist::observePlaylists);
    connect(this, &Playlist::songsChanged,
            this, &Playlist::observeSongs);
}

void Playlist::classBegin() {

}

void Playlist::componentComplete() {

}
