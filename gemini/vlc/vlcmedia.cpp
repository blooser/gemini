#include "vlcmedia.h"

#include "../paths/paths.h"

Q_LOGGING_CATEGORY(vlcMedia, "vlc.media")

using namespace vlc;

namespace {
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

QString VlcMedia::mrl() const {
    return libvlc_media_get_mrl(m_vlcMedia.get());
}

VlcMedia &VlcMedia::operator=(const QUrl &url) {
    qDebug() << url.toString().toUtf8().constData();
    m_vlcMedia.reset(libvlc_media_new_location(m_vlcInstance, url.toString().toUtf8().constData()));

    if (!m_vlcMedia) {
        qCWarning(vlcMedia) << "Creating new media failed!";
        return *this;
    }

    auto event_manager = libvlc_media_event_manager(m_vlcMedia.get());
    libvlc_event_attach(event_manager, libvlc_MediaParsedChanged, parse, this);

    libvlc_media_parse_with_options(m_vlcMedia.get(), PARSE_PATH[paths::getPath(url)], -1);

    return *this;
}

libvlc_media_type_t VlcMedia::mediaType() const {
    return libvlc_media_get_type(m_vlcMedia.get());
}

libvlc_media_t *VlcMedia::media() const {
    return m_vlcMedia.get();
}

bool VlcMedia::isParsed() const {
    return (libvlc_media_get_parsed_status(m_vlcMedia.get()) == libvlc_media_parsed_status_done);
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
