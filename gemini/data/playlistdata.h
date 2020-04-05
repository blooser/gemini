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

public:
    int m_id;
    QString m_name;

    friend inline bool operator==(const Playlist &playlist1, const Playlist &playlist2) {
        return (playlist1.m_id == playlist2.m_id);
    };

    friend inline bool operator!=(const Playlist &playlist1, const Playlist &playlist2) {
        return !(playlist1 == playlist2);
    };

    friend QDataStream &operator<<(QDataStream &out, const Playlist &playlist) {
        return out << playlist.m_id << playlist.m_name;
    }


    friend QDataStream &operator>>(QDataStream &in, Playlist &playlist) {
        return in >> playlist.m_id >> playlist.m_name;
    }
};

}

Q_DECLARE_METATYPE(data::Playlist)

#endif // PLAYLISTDATA_H
