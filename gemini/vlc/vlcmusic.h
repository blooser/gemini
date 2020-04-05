#ifndef VLCMUSIC_H
#define VLCMUSIC_H

#include "vlccore.h"

#include <QObject>

namespace vlc {

class VlcMusic : public VlcCore {
    Q_OBJECT

public:
    explicit VlcMusic(QObject *parent=nullptr);

    int volume() const;
    bool isMuted() const;

    void setVolume(const int volume);
    void setMute(const bool mute);
    void toggleMuted();
};

}

#endif // VLCMUSIC_H
