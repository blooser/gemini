#include "filescontroller.h"
#include "../paths/paths.h"

#include <QStandardPaths>
#include <QFile>
#include <QDir>

Q_LOGGING_CATEGORY(filesController, "files.controller")

namespace {
    const QHash<Enums::Data, QString> DATA {
        { Enums::Data::Wallpapers, QStringLiteral("wallpapers") },
        { Enums::Data::Songs, QStringLiteral("songs") }
    };
}

FilesController::FilesController(const QString &corePath, QObject *parent)
    : QObject(parent),
      m_corePath(corePath) {

    createDirectories();
}

QString FilesController::path() const {
    return m_corePath;
}

QStringList FilesController::subdirectories() const {
    return DATA.values();
}

bool FilesController::directoryExists(const QString &path) {
    return QDir(path).exists();
}

bool FilesController::fileExists(const QString &path) {
    return QFileInfo(path).exists();
}

void FilesController::createDirectories() {
    for (const auto &data : DATA.values()) {
        const QString dataPath = paths::join(m_corePath, data);

        if (!directoryExists(dataPath)) {
            qCInfo(filesController) << "Creating" << data << "directory";
            if (!QDir(dataPath).mkpath(".")) {
                qCWarning(filesController) << "Could not create path" << dataPath;
            }
        }
    }
}

QUrl FilesController::generateUrl(const QUrl &url, Enums::Data data) {
    return QUrl::fromLocalFile(paths::join(m_corePath, DATA.value(data), url.fileName()));
}

QUrl FilesController::put(const QUrl &url, Enums::Data data) {
    if (not url.isValid()) {
        qCWarning(filesController) << "Invalid url: " << url;
        return QString();
    }

    const QUrl newFileUrl = generateUrl(url, data);
    if (fileExists(newFileUrl.path())) {
        return newFileUrl;
    }

    return QFile::copy(url.path(), newFileUrl.path()) ? newFileUrl : QString();
}

void FilesController::remove(const QUrl &url) {
    if (!QFile::remove(url.path())) {
        qCWarning(filesController) << "Could not remove" << url << "Already deleted?";
    }
}
