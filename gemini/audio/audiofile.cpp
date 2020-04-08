#include "audiofile.h"

AudioFile::AudioFile(const QUrl &url)
    : m_url(url) {
    TagLib::FileRef file(m_url.path().toUtf8());

    auto tag = file.tag();
    m_isComplete = (tag->title() != TagLib::String::null);

    if (m_isComplete) {
        m_title = tag->title().toCString();
        m_artist = tag->artist().toCString();
        m_year = tag->year();
        m_album = tag->album().toCString();
        m_genre = tag->genre().toCString();
    } else {
        m_title = url.fileName();
    }

    // TODO: Do critical, audio can't have duration=0
    auto duration = file.audioProperties();
    m_duration = duration ? duration->length() : 0;
}

QUrl AudioFile::url() const {
    return m_url;
}

QString AudioFile::artist() const {
    return m_artist;
}

int AudioFile::year() const {
    return m_year;
}

QString AudioFile::title() const {
    return m_title;
}

QString AudioFile::album() const {
    return m_album;
}

int AudioFile::duration() const {
    return m_duration;
}

QString AudioFile::genre() const {
    return m_genre;
}

bool AudioFile::isComplete() const {
    return m_isComplete;
}
