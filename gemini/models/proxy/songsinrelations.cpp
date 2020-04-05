#include "songsinrelations.h"

Q_LOGGING_CATEGORY(songsInRelations, "songs.in.relations")

namespace {
    const QByteArray SONG_ROLENAME = QByteArrayLiteral("id");
    const QByteArray RELATION_PLAYLIST_ROLENAME = QByteArrayLiteral("playlist");
    const QByteArray RELATION_SONG_ROLENAME = QByteArrayLiteral("song");
}

SongsInRelations::SongsInRelations(QAbstractItemModel *songModel,  QAbstractItemModel *relationModel, QObject *parent)
    : QSortFilterProxyModel(parent),
      m_relations(relationModel) {

    setSourceModel(songModel);

    getRoleNames();
    setupConnections();
}

SongsInRelations::~SongsInRelations() {
    if (m_relations) {
        m_relations = nullptr;
    }
}

data::Playlist SongsInRelations::currentPlaylist() const {
    return m_currentPlaylist;
}

void SongsInRelations::setCurrentPlaylist(const data::Playlist &currentPlaylist) {
    if (m_currentPlaylist == currentPlaylist) {
        return;
    }

    m_currentPlaylist = currentPlaylist;
    emit currentPlaylistChanged(m_currentPlaylist);

    invalidateFilter();
}

bool SongsInRelations::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    if (!sourceModel() || !m_relations) {
        return false;
    }

    auto sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    auto songId = sourceModel()->data(sourceIndex, m_songRoleName);

    auto relationsIndex = m_relations->index(0, 0);
    auto playlists = m_relations->match(relationsIndex, m_relationPlaylistRoleName, m_currentPlaylist.m_id, -1, Qt::MatchExactly);

    QModelIndex songInRelationsIndex;
    for (const auto &playlist : qAsConst(playlists)) {
        songInRelationsIndex = m_relations->index(playlist.row(), 0);

        if (m_relations->data(songInRelationsIndex, m_relationSongRoleName).toInt() == songId.toInt() ) {
            return true;
        }
    }

    return false;
}

void SongsInRelations::getRoleNames() {
    m_songRoleName = sourceModel()->roleNames().key(SONG_ROLENAME);
    m_relationPlaylistRoleName = m_relations->roleNames().key(RELATION_PLAYLIST_ROLENAME);
    m_relationSongRoleName = m_relations->roleNames().key(RELATION_SONG_ROLENAME);
}

void SongsInRelations::setupConnections() {
    connect(m_relations, &QAbstractItemModel::modelReset,
            this, &SongsInRelations::invalidateFilter);
    connect(m_relations, &QAbstractItemModel::rowsInserted,
            this, &SongsInRelations::invalidateFilter);
    connect(m_relations, &QAbstractItemModel::rowsRemoved,
            this, &SongsInRelations::invalidateFilter);
}
