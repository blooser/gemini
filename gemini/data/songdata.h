#ifndef SONG_H
#define SONG_H

#include "playlistdata.h"

#include <QCoreApplication>
#include <QObject>
#include <QVector>
#include <QUrl>

namespace data {

struct Song {
    Q_GADGET
    Q_PROPERTY(int id MEMBER m_id)
    Q_PROPERTY(QString title MEMBER m_title)
    Q_PROPERTY(int duration MEMBER m_duration)
    Q_PROPERTY(QString artist MEMBER m_artist)
    Q_PROPERTY(QString date MEMBER m_date)
    Q_PROPERTY(QString album MEMBER m_album)
    Q_PROPERTY(QString genre MEMBER m_genre)
    Q_PROPERTY(bool completed MEMBER m_completed)
    Q_PROPERTY(QUrl url MEMBER m_url)
    Q_PROPERTY(data::Playlist playlist MEMBER m_playlist)

public:
    int m_id;
    QString m_title;
    int m_duration;
    QString m_artist;
    QString m_date;
    QString m_album;
    QString m_genre;
    bool m_completed;
    QUrl m_url;
    Playlist m_playlist;

    friend inline bool operator==(const Song &song1, const Song &song2) {
        return (song1.m_id == song2.m_id);
    };

    friend inline bool operator!=(const Song &song1, const Song &song2) {
        return !(song1 == song2);
    };

    friend QDataStream &operator<<(QDataStream &out, const Song &song) {
        return out << song.m_id << song.m_title << song.m_duration
                   << song.m_artist << song.m_date << song.m_album
                   << song.m_genre << song.m_completed << song.m_url
                   << song.m_playlist;
    }

    friend QDataStream &operator>>(QDataStream &in, Song &song) {
        return in >> song.m_id >> song.m_title >> song.m_duration
                  >> song.m_artist >> song.m_date >> song.m_album
                  >> song.m_genre >> song.m_completed >> song.m_url
                  >> song.m_playlist;
    }
};

}

Q_DECLARE_METATYPE(data::Song)

#endif // SONG_H
