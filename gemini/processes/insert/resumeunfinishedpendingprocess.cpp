#include "resumeunfinishedpendingprocess.h"

#include "songinsertprocess.h"
#include "wallpaperinsertprocess.h"
#include "../remove/pendingremoveprocess.h"

#include <QFileInfo>

namespace  {
    constexpr Enums::Data PENDING = Enums::Data::Pending;

    QByteArray URL_ROLENAME = QByteArrayLiteral("url");

    QStringList AUDIO_SUFFIXES {
        "mp3", "wav" // TODO: Add more suffixes
    };

    QStringList IMAGE_SUFFIXES {
        "png", "jpg", "jpeg" // TODO: Add more suffixes
    };
}

ResumeUnfinishedPendingProcess::ResumeUnfinishedPendingProcess(const std::shared_ptr<ModelController> &modelController,
                                                               const std::shared_ptr<FilesController> &filesController)
    : Process(QVariant()),
      m_modelController(modelController),
      m_filesController(filesController)
{

}

QVariantMap ResumeUnfinishedPendingProcess::modelData(const QVariant &) const {
    return QVariantMap();
}

void ResumeUnfinishedPendingProcess::start() {
    for (const auto &process : createInsertProcesses()) {
        if (process) { // Can be nullptr
            process->start();
        }
    }

    pendingFinished();
}

void ResumeUnfinishedPendingProcess::pendingFinished() {
    std::shared_ptr<Process> pendingRemoveProcess =  std::shared_ptr<Process>(new PendingRemoveProcess(m_modelController));
    pendingRemoveProcess->start();
}

QVector<QUrl> ResumeUnfinishedPendingProcess::collectUrls() const {
    QVector<QUrl> urls;
    for (const auto &url : m_modelController->readData(URL_ROLENAME, PENDING)) {
        urls.append(url.toUrl());
    }

    return urls;
}

std::shared_ptr<Process> ResumeUnfinishedPendingProcess::createInsertProcessByUrl(const QUrl &url) {
    if (isAudio(url)) {
        return std::shared_ptr<Process>(new SongInsertProcess(m_modelController, m_filesController, url));
    }

    if (isImage(url)) {
        return std::shared_ptr<Process>(new WallpaperInsertProcess(m_modelController, m_filesController, url));
    }

    return std::shared_ptr<Process>(nullptr);
}

QVector<std::shared_ptr<Process>> ResumeUnfinishedPendingProcess::createInsertProcesses() {
    auto urls = collectUrls();

    QVector<std::shared_ptr<Process>> processes;
    for (const auto &url : urls) {
        processes.append(createInsertProcessByUrl(url));
    }

    return processes;
}

bool ResumeUnfinishedPendingProcess::isAudio(const QUrl &url) {
    for (const auto &suffix : AUDIO_SUFFIXES) {
        if (QFileInfo(url.path()).suffix() == suffix) {
            return true;
        }
    }

    return false;
}

bool ResumeUnfinishedPendingProcess::isImage(const QUrl &url) {
    for (const auto &suffix : IMAGE_SUFFIXES) {
        if (QFileInfo(url.path()).suffix() == suffix) {
            return true;
        }
    }

    return false;
}
