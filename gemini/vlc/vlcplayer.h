#ifndef VLCMEDIAPLAYER_H
#define VLCMEDIAPLAYER_H

#include "../common/deleters.h"

#include "vlcmusic.h"

#include <vlc/vlc.h>
#include <memory>

#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(vlcPlayer)

namespace vlc {

class VlcMedia;

class VlcPlayer : public VlcMusic {
    Q_OBJECT

public:
    explicit VlcPlayer(QObject *parent = nullptr);

    int duration() const;
    int time() const;

    bool playing() const;

    void setMedia(const VlcMedia &vlcMedia);
    void setTime(const int time);

    void release();

    void play();
    void pause();
    void stop();
};

}

#endif // VLCMEDIAPLAYER_H
