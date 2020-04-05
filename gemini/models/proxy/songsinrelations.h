#ifndef SONGSINRELATIONS_H
#define SONGSINRELATIONS_H

#include "../../data/playlistdata.h"

#include <QObject>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(songsInRelations)

class SongsInRelations : public QSortFilterProxyModel {
    Q_OBJECT
    Q_PROPERTY(data::Playlist currentPlaylist READ currentPlaylist
               WRITE setCurrentPlaylist NOTIFY currentPlaylistChanged)

public:
    SongsInRelations(QAbstractItemModel *songModel,  QAbstractItemModel *relationModel, QObject *parent=nullptr);
    ~SongsInRelations();

    data::Playlist currentPlaylist() const;

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

public slots:
    void setCurrentPlaylist(const data::Playlist &currentPlaylist);

signals:
    void currentPlaylistChanged(const data::Playlist &currentPlaylist);

private:
    QAbstractItemModel* m_relations;

    data::Playlist m_currentPlaylist;

    int m_songRoleName;
    int m_relationPlaylistRoleName;
    int m_relationSongRoleName;

    void getRoleNames();
    void setupConnections();
};

#endif // SONGSINRELATIONS_H
