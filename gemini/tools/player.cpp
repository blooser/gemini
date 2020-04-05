#include "player.h"

Q_LOGGING_CATEGORY(player, "player")

using namespace vlc;

Player::Player(QObject *parent)
    : QObject(parent),
      m_status(Status::Stopped) {

    setupConnections();
}

void Player::setupConnections() {
    connect(this, &Player::sourceChanged,
            this, &Player::onSourceChanged, Qt::QueuedConnection);

    connect(&m_vlcPlayer, &VlcPlayer::timeChanged,
            this, &Player::timeChanged, Qt::QueuedConnection);
    connect(&m_vlcPlayer, &VlcPlayer::stateChanged,
            this, &Player::stateChanged, Qt::QueuedConnection);
    connect(&m_vlcPlayer, &VlcPlayer::muteChanged,
            this, &Player::muteChanged, Qt::QueuedConnection);
    connect(&m_vlcPlayer, &VlcPlayer::volumeChanged,
            this, &Player::volumeChanged, Qt::QueuedConnection);
    connect(&m_vlcPlayer, &VlcPlayer::mediaEnd,
            this, &Player::mediaEnd, Qt::QueuedConnection);

    connect(&m_vlcMedia, &VlcMedia::metaChanged,
            this, &Player::metaChanged, Qt::QueuedConnection);
}

void Player::onSourceChanged() {
    stop();

    if (not hasAudio()) {
        m_vlcPlayer.release();
        m_vlcMedia.release();
        emit sourceChanged(QUrl());
        return;
    }

    m_vlcMedia = libvlc_media_new_path(m_vlcPlayer.instance(), RAW_DATA(m_source.path()));
    m_vlcPlayer.setMedia(m_vlcMedia);

    play();
 }

void Player::stop() {
    m_vlcPlayer.stop();
    m_status = Status::Stopped;
    emit statusChanged(m_status);
}

void Player::play() {
    m_vlcPlayer.play();
    m_status = Status::Playing;
    emit statusChanged(m_status);
}

void Player::pause() {
    m_vlcPlayer.pause();
    m_status = Status::Paused;
    emit statusChanged(m_status);
}

void Player::toggle() {
    if (m_status == Status::Playing) {
        pause();
    } else {
        play();
    }
}

QUrl Player::source() const {
    return m_source;
}

Player::Status Player::status() const {
    return m_status;
}

int Player::volume() const {
    return m_vlcPlayer.volume();
}

int Player::duration() const {
    return m_vlcPlayer.duration();
}

int Player::time() {
    return m_vlcPlayer.time();
}

bool Player::muted() const {
    return m_vlcPlayer.isMuted();
}

bool Player::hasAudio() const {
    return m_source.isValid();
}

vlc::Meta Player::meta() const {
    return m_vlcMedia.meta();
}

void Player::setSource(const QUrl &source) {
    if (m_source == source) {
        return;
    }

    m_source = source;
    emit sourceChanged(m_source);
}

void Player::setVolume(const int volume) {
    m_vlcPlayer.setVolume(volume);
}

void Player::setMute(const bool mute) {
    m_vlcPlayer.setMute(mute);
}

void Player::setTime(const int time) {
    m_vlcPlayer.setTime(time);
}

void Player::classBegin() {

}

void Player::componentComplete() {

}
