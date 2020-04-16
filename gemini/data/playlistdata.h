#ifndef PLAYLISTDATA_H
#define PLAYLISTDATA_H

#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QDataStream>

namespace data {

struct Playlist {
    Q_GADGET
    Q_PROPERTY(int id MEMBER m_id)
    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(int songs MEMBER m_songs)
    Q_PROPERTY(int duration MEMBER m_duration)

public:
    int m_id;
    QString m_name;
    int m_songs;
    int m_duration;

    friend inline bool operator==(const Playlist &playlist1, const Playlist &playlist2) {
        return (playlist1.m_id == playlist2.m_id);
    };

    friend inline bool operator!=(const Playlist &playlist1, const Playlist &playlist2) {
        return !(playlist1 == playlist2);
    };

    friend QDataStream &operator<<(QDataStream &out, const Playlist &playlist) {
        return out << playlist.m_id << playlist.m_name
                   << playlist.m_songs << playlist.m_duration;
    }


    friend QDataStream &operator>>(QDataStream &in, Playlist &playlist) {
        return in >> playlist.m_id >> playlist.m_name
                  >> playlist.m_songs >> playlist.m_duration;
    }
};

}

Q_DECLARE_METATYPE(data::Playlist)

#endif // PLAYLISTDATA_H
