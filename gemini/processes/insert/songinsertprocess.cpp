#include "songinsertprocess.h"

#include "../../common/enums.h"

namespace {
    constexpr Enums::Data SONGS = Enums::Data::Songs;
}

SongInsertProcess::SongInsertProcess(const std::shared_ptr<ModelController> &modelController,
                                     const std::shared_ptr<FilesController> &filesController,
                                     const QVariant &data)
    : PendableProcess(data, modelController),
    m_modelController(modelController),
    m_filesController(filesController) {

}

QVariantMap SongInsertProcess::modelData(const QVariant &data) const {
    return {
        { "name", data.toUrl().fileName() },
        { "url", data.toUrl() }
    };
}

void SongInsertProcess::start() {
    auto newUrl = m_filesController->put(inputData().toUrl(), SONGS);
    if (not newUrl.isEmpty()) {
        m_modelController->appendData(modelData(newUrl), SONGS);
        finishPending();
    }
}
