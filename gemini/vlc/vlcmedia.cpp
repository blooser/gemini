#include "vlcmedia.h"

#include "../paths/paths.h"

Q_LOGGING_CATEGORY(vlcMedia, "vlc.media")

using namespace vlc;

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
    }

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
