#include "playlistremoveprocess.h"

namespace {
    constexpr Enums::Data PLAYLIST = Enums::Data::Playlist;
    constexpr Enums::Data RELATIONS = Enums::Data::Relations;
}

PlaylistRemoveProcess::PlaylistRemoveProcess(const std::shared_ptr<ModelController> &modelController,
                                             const QVariant &data)
            : Process(data),
            m_modelController(modelController) {

}

QVariantMap PlaylistRemoveProcess::modelData(const QVariant &data) const {
    return {
        { "id", data.toInt() }
    };
}

QVariantMap PlaylistRemoveProcess::relationsModelData(const QVariant &data) const {
    return {
        { "playlist", data.toInt()}
    };
}

void PlaylistRemoveProcess::start() {
    if (inputData().toInt()) {
        m_modelController->removeData(modelData(inputData()), PLAYLIST);
        m_modelController->removeData(relationsModelData(inputData()), RELATIONS);
    }
}
