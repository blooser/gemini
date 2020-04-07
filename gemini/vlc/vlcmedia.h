#ifndef VLCMEDIA_H
#define VLCMEDIA_H

#include "vlcmeta.h"

#include "../common/deleters.h"
#include "../paths/paths.h"

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

    void loadMeta();
    void release();
    void processParsed();

    int duration() const;
    Meta meta() const;

    bool isParsed() const;
    bool isParsedError() const;

    QUrl path() const;
    QString mrl() const;

    libvlc_media_parsed_status_t parsedStatus() const;
    libvlc_media_type_t mediaType() const;
    libvlc_media_t *media() const;

    static void parse(const libvlc_event_t *event, void *data);

signals:
    void metaChanged(const vlc::Meta &meta);

private:
    QUrl m_path;

    libvlc_media_parsed_status_t m_parsedStatus;
    libvlc_instance_t *m_vlcInstance;
    std::unique_ptr<libvlc_media_t, VlcMediaDeleter> m_vlcMedia;

    Meta m_meta;
};

}

#endif // VLCMEDIA_H
