#include "vlccore.h"

Q_LOGGING_CATEGORY(vlcCore, "vlc.core")

using namespace vlc;

VlcCore::VlcCore(QObject *parent)
    : QObject(parent) {

    initialize();
}

void VlcCore::initialize() {
    m_vlcInstance = std::unique_ptr<libvlc_instance_t, VlcInstanceDeleter>(libvlc_new(0, nullptr));
    if (!m_vlcInstance) {
        qCCritical(vlcCore) << "Could not initialize VLC instance!" << libvlc_errmsg();
        std::exit(1);
    }

    libvlc_set_user_agent(m_vlcInstance.get(), ProjectName, "Gemini Music Player");
    libvlc_set_app_id(m_vlcInstance.get(), "com.blooser.gemini", ProjectVersion, ProjectName);

    m_vlcMediaPlayer = std::unique_ptr<libvlc_media_player_t, VlcMediaPlayerDeleter>(libvlc_media_player_new(m_vlcInstance.get()));
    if (!m_vlcMediaPlayer) {
        qCCritical(vlcCore) << "Could not initialize media player!" << libvlc_errmsg();
        std::exit(1);
    }

    listenEvents();
}

void VlcCore::listen(const libvlc_event_t *event, void *data) {
    if (auto vlcCore = static_cast<VlcCore*>(data)) {
        switch (event->type) {
            case libvlc_MediaPlayerTimeChanged:
                vlcCore->timeChanged();
                break;
            case libvlc_MediaPlayerMediaChanged:
            case libvlc_MediaPlayerPlaying:
            case libvlc_MediaPlayerPaused:
            case libvlc_MediaPlayerStopped:
                vlcCore->stateChanged();
                break;
            case libvlc_MediaPlayerMuted:
            case libvlc_MediaPlayerUnmuted:
                vlcCore->muteChanged();
                break;
            case libvlc_MediaPlayerAudioVolume:
                vlcCore->volumeChanged();
                break;
            case libvlc_MediaPlayerEndReached:
                vlcCore->mediaEnd();
        }
    }
}

void VlcCore::listenEvents() {
    libvlc_event_manager_t *eventManager = libvlc_media_player_event_manager(m_vlcMediaPlayer.get());

    if (!eventManager) {
        qCWarning(vlcCore) << "Could not get media player event manager!";
        return;
    }

    for (libvlc_event_type_t event = libvlc_MediaPlayerMediaChanged; event <= libvlc_MediaPlayerVout; ++event) {
        switch (event) {
            case libvlc_MediaPlayerMuted:
            case libvlc_MediaPlayerUnmuted:
            case libvlc_MediaPlayerPlaying:
            case libvlc_MediaPlayerAudioVolume:
            case libvlc_MediaPlayerMediaChanged:
            case libvlc_MediaPlayerStopped:
            case libvlc_MediaPlayerPaused:
            case libvlc_MediaPlayerTimeChanged:
            case libvlc_MediaPlayerEndReached:
                libvlc_event_attach(eventManager, event, &VlcCore::listen, this);
                break;
        }
    }
}

libvlc_instance_t *VlcCore::instance() const {
    return m_vlcInstance.get();
}

libvlc_media_player_t *VlcCore::mediaPlayer() const {
    return m_vlcMediaPlayer.get();
}
