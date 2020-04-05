#ifndef RELATIONPROCESS_H
#define RELATIONPROCESS_H

#include "../process.h"

#include "songinsertprocess.h"
#include "pendinginsertprocess.h"

#include "../../common/deleters.h"

#include "../../controllers/filescontroller.h"
#include "../../controllers/modelcontroller.h"

#include <memory>

#include <QObject>
#include <QVector>

class RelationInsertProcess : public Process {
public:
    RelationInsertProcess(const std::shared_ptr<ModelController> &modelController,
                          const std::shared_ptr<FilesController> &filesController,
                          const QVariant &data);

    QVariantMap modelData(const QVariant &data) const override;
    void start() override;

protected:
    bool containsFiles() const;
    void processPending(const QVariantList &files);
    void processSongs(const QVariantList &data);
    void processRelations(const QVector<int> &songIds);
    void processPendingDelete();

private:
    std::shared_ptr<ModelController> m_modelController;
    std::shared_ptr<FilesController> m_filesController;

    QVector<std::shared_ptr<SongInsertProcess>> prepareSongProcesses(const QVariantList &data) const;
    QVector<int> collectSongIds(const QVector<QUrl> &songUrls) const;
    QVariantList prepareRelationsData(const QVector<int> &songIds) const;
    QVector<std::shared_ptr<RelationInsertProcess>> prepareRelationsProcesses(const QVector<int> &songIds) const;
    QVector<QUrl> generateNewUrls(const QVariantList &files);
    QVariantMap modelDataWithCurrentPlaylist(const int &songId) const;
};

#endif // RELATIONPROCESS_H
