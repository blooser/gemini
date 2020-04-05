#ifndef VLCMEDIA_H
#define VLCMEDIA_H

#include "vlcmeta.h"

#include "../common/deleters.h"

#include <vlc/vlc.h>
#include <memory>

#include <QObject>
#include <QUrl>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(vlcMedia)

#define RAW_DATA(str) str.toUtf8().constData()

namespace vlc {

class VlcMedia : public QObject {
    Q_OBJECT

public:
    explicit VlcMedia(QObject *parent=nullptr);

    VlcMedia& operator=(libvlc_media_t *media);
    void loadMeta();
    void release();
    Meta meta() const;

    libvlc_media_t *media() const;

    static void parse(const libvlc_event_t *event, void *data);

signals:
    void metaChanged();

private:
    std::unique_ptr<libvlc_media_t, VlcMediaDeleter> m_vlcMedia;
    Meta m_meta;
};

}

#endif // VLCMEDIA_H
