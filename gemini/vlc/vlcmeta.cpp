#include "vlcmeta.h"

#include <QMap>

using namespace vlc;

namespace {
    const QMap<QString, libvlc_meta_t> META_DATA {
        { QStringLiteral("title"), libvlc_meta_Title },
        { QStringLiteral("artist"), libvlc_meta_Artist },
        { QStringLiteral("url"), libvlc_meta_URL },
        { QStringLiteral("date"), libvlc_meta_Date }
    };
}

Meta Meta::load(libvlc_media_t *vlcMedia) {
    return Meta {
        libvlc_media_get_meta(vlcMedia, META_DATA.value("title")),
        libvlc_media_get_meta(vlcMedia, META_DATA.value("artist")),
        libvlc_media_get_meta(vlcMedia, META_DATA.value("url")),
        libvlc_media_get_meta(vlcMedia, META_DATA.value("date"))
    };
}
