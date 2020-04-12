#ifndef VLCMEDIA_H
#define VLCMEDIA_H

#include "../common/deleters.h"

#include <vlc/vlc.h>
#include <memory>

#include <QObject>
#include <QUrl>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(vlcMedia)

namespace vlc {

class VlcMedia : public QObject {
    Q_OBJECT

public:
    explicit VlcMedia(libvlc_instance_t *vlcInstance, QObject *parent=nullptr);

    VlcMedia& operator=(const QUrl &url);

    QUrl path() const;
    QString mrl() const;

    libvlc_media_type_t mediaType() const;
    libvlc_media_t *media() const;

private:
    QUrl m_path;

    libvlc_instance_t *m_vlcInstance;
    std::unique_ptr<libvlc_media_t, VlcMediaDeleter> m_vlcMedia;
};

}

#endif // VLCMEDIA_H
