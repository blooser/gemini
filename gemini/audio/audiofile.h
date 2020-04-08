#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tpropertymap.h>

#include <QUrl>
#include <QString>

class AudioFile {
public:
    AudioFile(const QUrl &url);

    QUrl url() const;

    QString title() const;
    QString artist() const;
    QString album() const;
    QString genre() const;

    int year() const;
    int duration() const;

    bool isComplete() const;

private:
    QUrl m_url;

    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;

    int m_year;
    int m_duration;

    bool m_isComplete;
};

#endif // AUDIOFILE_H
