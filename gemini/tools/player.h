#ifndef PLAYER_H
#define PLAYER_H

#include "../vlc/vlcmedia.h"
#include "../vlc/vlcplayer.h"

#include "../common/deleters.h"

#include <vlc/vlc.h>
#include <memory>

#include <QObject>
#include <QUrl>
#include <QQmlParserStatus>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(player)

#define RAW_DATA(str) str.toUtf8().constData()

class Player : public QObject,
               public QQmlParserStatus {
    Q_INTERFACES(QQmlParserStatus)
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source
               WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(Status status READ status
               NOTIFY statusChanged)
    Q_PROPERTY(int volume READ volume
              WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(int time READ time
               WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(int duration READ duration
               NOTIFY stateChanged)
    Q_PROPERTY(bool muted READ muted
               WRITE setMute NOTIFY muteChanged)
    Q_PROPERTY(bool hasAudio READ hasAudio
               NOTIFY sourceChanged)

public:
    enum Status {
        Playing,
        Paused,
        Stopped
    };
    Q_ENUM(Status)

    explicit Player(QObject *parent = nullptr);

    Q_INVOKABLE void play();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void toggle();

    QUrl source() const;
    void setSource(const QUrl &source);

    Status status() const;

    int volume() const;
    void setVolume(const int volume);

    int time();
    void setTime(const int time);

    bool muted() const;
    void setMute(const bool mute);

    int duration() const;
    bool hasAudio() const;

    // QQmlParserStatus
    void classBegin() override;
    void componentComplete() override;

private slots:
    void onSourceChanged();

signals:
    void sourceChanged(const QUrl &source);
    void statusChanged(const Status status);

    void volumeChanged();
    void timeChanged();
    void muteChanged();
    void stateChanged();
    void mediaEnd();

private:
    QUrl m_source;
    Status m_status;

    vlc::VlcPlayer m_vlcPlayer;
    vlc::VlcMedia m_vlcMedia;

    void setupConnections();
};

#endif // PLAYER_H
