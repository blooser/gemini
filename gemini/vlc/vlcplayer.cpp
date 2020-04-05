#include "vlcplayer.h"
#include "vlcmedia.h"

Q_LOGGING_CATEGORY(vlcPlayer, "vlc.player")

using namespace vlc;

VlcPlayer::VlcPlayer(QObject *parent)
    : VlcMusic(parent) {

}

bool VlcPlayer::playing() const {
    if (mediaPlayer()) {
        return libvlc_media_player_is_playing(mediaPlayer());
    }

    return false;
}

int VlcPlayer::duration() const {
    if (mediaPlayer()) {
        return libvlc_media_player_get_length(mediaPlayer());
    }

    return -1;
}

int VlcPlayer::time() const {
    if (mediaPlayer()) {
        return libvlc_media_player_get_time(mediaPlayer());
    }

    return -1;
}

void VlcPlayer::release() {
    if (mediaPlayer()) {
        libvlc_media_release(libvlc_media_player_get_media(mediaPlayer()));
    }
}

void VlcPlayer::play() {
    if (mediaPlayer() && !playing()) {
        libvlc_media_player_play(mediaPlayer());
    }
}

void VlcPlayer::pause() {
    if (mediaPlayer() && playing()) {
        libvlc_media_player_pause(mediaPlayer());
    }
}

void VlcPlayer::stop() {
    if (mediaPlayer() && playing()) {
        libvlc_media_player_stop(mediaPlayer());
    }
}

void VlcPlayer::setMedia(const VlcMedia &vlcMedia) {
    if (mediaPlayer()) {
        libvlc_media_player_set_media(mediaPlayer(), vlcMedia.media());
    }
}

void VlcPlayer::setTime(const int time) {
    if (mediaPlayer()) {
        libvlc_media_player_set_time(mediaPlayer(), time);
    }
}
