#ifndef VLCCORE_H
#define VLCCORE_H

#include "../common/deleters.h"

#include <vlc/vlc.h>
#include <memory>

#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(vlcCore)

namespace vlc {

class VlcCore : public QObject {
    Q_OBJECT

public:
    explicit VlcCore(QObject *parent=nullptr);

     libvlc_instance_t *instance() const;
     libvlc_media_player_t *mediaPlayer() const;

signals:
     void muteChanged();
     void timeChanged();
     void durationChanged();
     void volumeChanged();
     void stateChanged();
     void mediaEnd();

protected:
     static void listen(const libvlc_event_t *event, void *data);

private:
    std::unique_ptr<libvlc_media_player_t, VlcMediaPlayerDeleter> m_vlcMediaPlayer;
    std::unique_ptr<libvlc_instance_t, VlcInstanceDeleter> m_vlcInstance;

    void initialize();
    void listenEvents();
};

}

#endif // VLCCORE_H
