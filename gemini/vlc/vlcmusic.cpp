#include "vlcmusic.h"

using namespace vlc;

VlcMusic::VlcMusic(QObject *parent)
    : VlcCore(parent) {

}

int VlcMusic::volume() const {
    if (mediaPlayer()) {
        return libvlc_audio_get_volume(mediaPlayer());
    }

    return -1;
}

bool VlcMusic::isMuted() const {
    if (mediaPlayer()) {
        return libvlc_audio_get_mute(mediaPlayer());
    }

    return false;
}

void VlcMusic::setVolume(const int volume) {
    if (mediaPlayer()) {
        libvlc_audio_set_volume(mediaPlayer(), volume);
    }
}

void VlcMusic::setMute(const bool mute) {
    if (mediaPlayer()) {
        libvlc_audio_set_mute(mediaPlayer(), mute);
    }
}

void VlcMusic::toggleMuted() {
    if (mediaPlayer()) {
        libvlc_audio_toggle_mute(mediaPlayer());
    }
}
