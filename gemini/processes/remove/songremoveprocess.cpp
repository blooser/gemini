#include "songremoveprocess.h"

namespace {
    constexpr Enums::Data SONGS = Enums::Data::Songs;
    constexpr Enums::Data RELATIONS = Enums::Data::Relations;
}

SongRemoveProcess::SongRemoveProcess(const std::shared_ptr<ModelController> &modelController,
                                     const std::shared_ptr<FilesController> &filesController,
                                     const QVariant &data)
    : Process(data),
    m_modelController(modelController),
    m_filesController(filesController) {

}

QVariantMap SongRemoveProcess::modelData(const QVariant &data) const {
    return {
        { "id", data.toMap().value("id").toInt() }
    };
}

QVariantMap SongRemoveProcess::relationsModelData(const QVariant &data) const {
    return {
        { "song", data.toMap().value("id")}
    };
}

void SongRemoveProcess::start() {
    if (not inputData().toMap().isEmpty()) {
        m_filesController->remove(inputData().toMap().value("url").toUrl().path());
        m_modelController->removeData(modelData(inputData()), SONGS);
        m_modelController->removeData(relationsModelData(inputData()), RELATIONS);
    }
}
