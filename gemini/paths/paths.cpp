#include "paths.h"

#include <QObject>
#include <QFileInfo>

namespace paths {

bool isAudio(const QUrl &url) {
    for (const auto &suffix : qAsConst(AUDIO_SUFFIXES)) {
        if (QFileInfo(url.path()).suffix() == suffix) {
            return true;
        }
    }

    return false;
}

bool isImage(const QUrl &url) {
    for (const auto &suffix : qAsConst(IMAGE_SUFFIXES)) {
        if (QFileInfo(url.path()).suffix() == suffix) {
            return true;
        }
    }

    return false;
}

bool isLocal(const QUrl &url) {
    const QString &scheme = url.scheme();

    return scheme == QLatin1String("file")
        or scheme == QLatin1String("data");
}

bool isRemote(const QUrl &url) {
    const QString &scheme = url.scheme();

    return scheme == QLatin1String("http")
        or scheme == QLatin1String("https");
}

Path getPath(const QUrl &url) {
    if (isLocal(url)) {
        return Path::Local;
    }

    if (isRemote(url)) {
        return Path::Remote;
    }

    return Path::Unknown;
}

}
