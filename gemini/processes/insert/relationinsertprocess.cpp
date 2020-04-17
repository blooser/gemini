#include "relationinsertprocess.h"

#include "../remove/pendingremoveprocess.h"

#include "../../common/enums.h"

#include <QMap>

namespace {
    constexpr Enums::Data RELATIONS = Enums::Data::Relations;
    constexpr Enums::Data SONGS = Enums::Data::Songs;
}

RelationInsertProcess::RelationInsertProcess(const std::shared_ptr<ModelController> &modelController,
                                 const std::shared_ptr<FilesController> &filesController,
                                 const QVariant &data)
            : Process(data),
            m_modelController(modelController),
            m_filesController(filesController) {

}

bool RelationInsertProcess::containsFiles() const {
    return inputData().toMap().contains("files");
}

QVariantMap RelationInsertProcess::modelData(const QVariant &data) const {
    return {
        { "playlist", data.toMap().value("playlist") },
        { "song", data.toMap().value("song") }
    };
}

QVector<int> RelationInsertProcess::collectSongIds(const QVector<QUrl> &songUrls) const {
    QVector<int> songIds;
    for (const auto &songUrl : songUrls) {
        auto songId = m_modelController->findBuddy({{"url", songUrl}}, "id", SONGS).first(); // NOTE: Default hints is 1, so, there will be returned only one element and vice versa
        if (songId.isValid() && songId.toInt() != 0) {
            songIds.append(songId.toInt());
        }
    }

    return songIds;
}

void RelationInsertProcess::processPending(const QVariantList &files) {
    auto pendingProcess = std::shared_ptr<PendingInsertProcess>(new PendingInsertProcess(m_modelController, files));
    pendingProcess->start();
}

void RelationInsertProcess::processPendingDelete() {
    std::shared_ptr<PendingRemoveProcess> pendingDeleteProcess(new PendingRemoveProcess(m_modelController));
    pendingDeleteProcess->start();
}

QVector<std::shared_ptr<SongInsertProcess>> RelationInsertProcess::prepareSongProcesses(const QVariantList &data) const {
    QVector<std::shared_ptr<SongInsertProcess>> songProcesses;

    for (const auto &url : data) {
        songProcesses.append(std::shared_ptr<SongInsertProcess>(new SongInsertProcess(m_modelController,
                                                                                      m_filesController,
                                                                                      url)));
    }

    return songProcesses;
}

void RelationInsertProcess::processSongs(const QVariantList &data) {
    for (const auto &songProcess : prepareSongProcesses(data)) {
        songProcess->start();
    }
}

QVector<std::shared_ptr<RelationInsertProcess>> RelationInsertProcess::prepareRelationsProcesses(const QVector<int> &songIds) const{
    QVector<std::shared_ptr<RelationInsertProcess>> relationProcesses;
    auto data = prepareRelationsData(songIds);
    for (const auto &item : data) {
        relationProcesses.append(std::shared_ptr<RelationInsertProcess>(new RelationInsertProcess(m_modelController,
                                                                                                  m_filesController,
                                                                                                  item)));
    }

    return relationProcesses;
}

void RelationInsertProcess::processRelations(const QVector<int> &songIds) {
    for (const auto &relationProcess : prepareRelationsProcesses(songIds)) {
        relationProcess->start();
    }
}

QVariantMap RelationInsertProcess::modelDataWithCurrentPlaylist(const int &songId) const{
    return {
        { "playlist", inputData().toMap().value("playlist") },
        { "song", songId }
    };
}

QVariantList RelationInsertProcess::prepareRelationsData(const QVector<int> &songIds) const {
    QVariantList relationsData;
    for (const auto & songId : songIds) {
        relationsData.append(modelDataWithCurrentPlaylist(songId));
    }

    return relationsData;
}

QVector<QUrl> RelationInsertProcess::generateNewUrls(const QVariantList &files) {
    QVector<QUrl> songUrls;
    for (const auto &file : files) {
        songUrls.append(m_filesController->generateUrl(file.toUrl(), SONGS));
    }

    return songUrls;
}

void RelationInsertProcess::start() {
    if (not containsFiles() and not inputData().toMap().isEmpty()) {
        m_modelController->appendData(modelData(inputData()), RELATIONS);
        return;
    }

    auto files = inputData().toMap().value("files").toList();
    if (files.isEmpty()) {
        return;
    }

    processPending(files);
    processSongs(files);
    processPendingDelete();

    auto songUrls = generateNewUrls(files);
    auto songIds = collectSongIds(songUrls);
    processRelations(songIds);
}
