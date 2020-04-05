#ifndef SONG_H
#define SONG_H

#include "playlistdata.h"

#include <QCoreApplication>
#include <QObject>
#include <QVector>
#include <QString>

namespace data {

struct Song {
    Q_GADGET
    Q_PROPERTY(int id MEMBER m_id)
    Q_PROPERTY(QString url MEMBER m_url)
    Q_PROPERTY(data::Playlist playlist MEMBER m_playlist)

public:
    int m_id;
    QString m_url;
    Playlist m_playlist;

    friend inline bool operator==(const Song &song1, const Song &song2) {
        return (song1.m_id == song2.m_id);
    };

    friend inline bool operator!=(const Song &song1, const Song &song2) {
        return !(song1 == song2);
    };

    friend QDataStream &operator<<(QDataStream &out, const Song &song) {
        return out << song.m_id << song.m_url << song.m_playlist;
    }

    friend QDataStream &operator>>(QDataStream &in, Song &song) {
        return in >> song.m_id >> song.m_url >> song.m_playlist;
    }
};

}

Q_DECLARE_METATYPE(data::Song)

#endif // SONG_H
