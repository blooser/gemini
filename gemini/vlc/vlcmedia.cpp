#include "vlcmedia.h"

#include "../paths/paths.h"

Q_LOGGING_CATEGORY(vlcMedia, "vlc.media")

using namespace vlc;

namespace {
    constexpr int PARSE_TIMEOUT = 100; // TODO: 100 is enough?

    QMap<paths::Path, libvlc_media_parse_flag_t> PARSE_PATH {
        { paths::Path::Local, libvlc_media_parse_flag_t::libvlc_media_parse_local },
        { paths::Path::Remote, libvlc_media_parse_flag_t::libvlc_media_parse_network }
    };
}

VlcMedia::VlcMedia(libvlc_instance_t *vlcInstance, QObject *parent)
    : QObject(parent),
      m_vlcInstance(vlcInstance),
      m_vlcMedia(nullptr) {

}

VlcMedia &VlcMedia::operator=(const QUrl &url) {
    if (not m_vlcInstance) {
        qCWarning(vlcMedia) << "There is no VLC instance!";
        return *this;
    }

    m_path = url;
    m_vlcMedia.reset(libvlc_media_new_location(m_vlcInstance, m_path.toString().toUtf8().constData()));

    if (not m_vlcMedia) {
        qCWarning(vlcMedia) << "Creating new media failed!";
        return *this;
    }

    // TODO: check for memory issues on every repeat this operation
    auto event_manager = libvlc_media_event_manager(m_vlcMedia.get());
    libvlc_event_attach(event_manager, libvlc_MediaParsedChanged, parse, this);

    libvlc_media_parse_with_options(m_vlcMedia.get(), PARSE_PATH[paths::getPath(url)], PARSE_TIMEOUT);

    return *this;
}

libvlc_media_type_t VlcMedia::mediaType() const {
    return libvlc_media_get_type(m_vlcMedia.get());
}

QUrl VlcMedia::path() const {
    return m_path;
}

QString VlcMedia::mrl() const {
    return libvlc_media_get_mrl(m_vlcMedia.get());
}

libvlc_media_t *VlcMedia::media() const {
    return m_vlcMedia.get();
}

bool VlcMedia::isParsed() const {
    return (m_parsedStatus == libvlc_media_parsed_status_done);
}

bool VlcMedia::isParsedError() const {
    return (m_parsedStatus == libvlc_media_parsed_status_failed);
}

libvlc_media_parsed_status_t VlcMedia::parsedStatus() const {
    return m_parsedStatus;
}

int VlcMedia::duration() const {
    return libvlc_media_get_duration(m_vlcMedia.get());
}

Meta VlcMedia::meta() const {
    return m_meta;
}

void VlcMedia::parse(const libvlc_event_t *event, void *data) {
    if (event->type == libvlc_MediaParsedChanged) {
        if (auto vlcMedia = static_cast<VlcMedia*>(data)) {
            vlcMedia->processParsed();
        }
    }
}

void VlcMedia::processParsed() {
    m_parsedStatus = libvlc_media_get_parsed_status(m_vlcMedia.get());

    if (isParsed()) {
        loadMeta();
        return;
    }

    if (isParsedError()) {
        qCWarning(vlcMedia) << "Failed to parse path:" << m_path;
    }
}

void VlcMedia::release() {
    m_vlcMedia.reset(nullptr);
    m_meta = Meta{};
    emit metaChanged(m_meta);
}

void VlcMedia::loadMeta() {
    m_meta = Meta::load(m_vlcMedia.get());
    emit metaChanged(m_meta);
}
