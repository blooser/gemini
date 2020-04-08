#include "vlcmeta.h"

#include <QMap>

using namespace vlc;

namespace {
    const QMap<QString, libvlc_meta_t> META_DATA {
        { QStringLiteral("title"), libvlc_meta_Title },
        { QStringLiteral("artist"), libvlc_meta_Artist },
        { QStringLiteral("date"), libvlc_meta_Date },
        { QStringLiteral("album"), libvlc_meta_Album },
        { QStringLiteral("genre"), libvlc_meta_Genre }
    };
}

Meta Meta::load(libvlc_media_t *vlcMedia) {
    return Meta {
        libvlc_media_get_meta(vlcMedia, META_DATA.value("title")),
        libvlc_media_get_meta(vlcMedia, META_DATA.value("artist")),
        libvlc_media_get_meta(vlcMedia, META_DATA.value("date")),
        libvlc_media_get_meta(vlcMedia, META_DATA.value("album")),
        libvlc_media_get_meta(vlcMedia, META_DATA.value("genre"))
    };
}
