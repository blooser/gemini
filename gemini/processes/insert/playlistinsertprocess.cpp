#include "playlistinsertprocess.h"

namespace {
    constexpr Enums::Data PLAYLIST = Enums::Data::Playlist;
}

PlaylistInsertProcess::PlaylistInsertProcess(const std::shared_ptr<ModelController> &modelController,
                                 const QVariant &data)
            : Process(data),
            m_modelController(modelController) {

}

QVariantMap PlaylistInsertProcess::modelData(const QVariant &data) const {
    return {
        { "name", data.toString() }
    };
}

void PlaylistInsertProcess::start() {
    if (not inputData().toString().isEmpty()) {
        m_modelController->appendData(modelData(inputData()), PLAYLIST);
    }
}
