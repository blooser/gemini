#ifndef DELETERS_H
#define DELETERS_H

#include <vlc/vlc.h>

#include <QObject>

struct QObjectDeleter {
    void operator()(QObject *qobject) {
        if (qobject) {
            qobject->deleteLater();
        }
    }
};

struct VlcInstanceDeleter {
    void operator()(libvlc_instance_t *instance) {
        if (instance) {
            libvlc_release(instance);
        }
    };
};

struct VlcMediaDeleter {
    void operator()(libvlc_media_t *media) {
        if (media) {
            libvlc_media_release(media);
        }
    }
};

struct VlcMediaPlayerDeleter {
    void operator()(libvlc_media_player_t *mediaPlayer) {
        if (mediaPlayer) {
            if (libvlc_media_player_is_playing(mediaPlayer)) {
                libvlc_media_player_stop(mediaPlayer);
            }

            libvlc_media_player_release(mediaPlayer);
        }
    }
};

#endif // DELETERS_H
