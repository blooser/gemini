#ifndef PATHS_H
#define PATHS_H

#include <QStringList>
#include <QString>
#include <QUrl>

namespace paths {

enum class Path {
    Unknown = -1,

    Local,
    Remote
};

const QStringList AUDIO_SUFFIXES {
    QStringLiteral("mp3"),
    QStringLiteral("wav")
    // TODO: Add more suffixes
};

const QStringList IMAGE_SUFFIXES {
    QStringLiteral("png"),
    QStringLiteral("jpg"),
    QStringLiteral("jpeg")
    // TODO: Add more suffixes
};


bool isAudio(const QUrl &url);
bool isImage(const QUrl &url);

bool isLocal(const QUrl &url);
bool isRemote(const QUrl &url);

Path getPath(const QUrl &url);

template <typename ...Paths>
QString join(const QString &root, Paths ...paths) {
    return (root + ... + (QStringLiteral("/") + QString(paths)));
}

}

#endif // PATHS_H
