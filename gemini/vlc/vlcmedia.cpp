#include "vlcmedia.h"

Q_LOGGING_CATEGORY(vlcMedia, "vlc.media")

using namespace vlc;

namespace {
    constexpr int PARSE_TIMEOUT = 100;
}

VlcMedia::VlcMedia(QObject *parent)
    : QObject(parent),
      m_vlcMedia(nullptr) {
}

VlcMedia &VlcMedia::operator=(libvlc_media_t *media) {
    m_vlcMedia.reset(media);
    if (!m_vlcMedia) {
        qCWarning(vlcMedia) << "Creating new media failed!";
        return *this;
    }

    auto event_manager = libvlc_media_event_manager(media);
    libvlc_event_attach(event_manager, libvlc_MediaParsedChanged, parse, this);

    libvlc_media_parse_with_options(m_vlcMedia.get(), libvlc_media_parse_flag_t::libvlc_media_parse_local, PARSE_TIMEOUT);

    return *this;
}

libvlc_media_t *VlcMedia::media() const {
    return m_vlcMedia.get();
}

Meta VlcMedia::meta() const {
    return m_meta;
}

void VlcMedia::parse(const libvlc_event_t *event, void *data) {
    if (event->type == libvlc_MediaParsedChanged) {
        if (auto vlcMedia = static_cast<VlcMedia*>(data)) {
            vlcMedia->loadMeta();
        }
    }
}

void VlcMedia::release() {
    m_vlcMedia.reset(nullptr);
    m_meta = Meta{};
    emit metaChanged();
}

void VlcMedia::loadMeta() {
    m_meta = Meta::load(m_vlcMedia.get());
    emit metaChanged();
}
