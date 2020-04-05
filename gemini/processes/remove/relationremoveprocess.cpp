#include "relationremoveprocess.h"

namespace {
    constexpr Enums::Data RELATIONS = Enums::Data::Relations;
}

RelationRemoveProcess::RelationRemoveProcess(const std::shared_ptr<ModelController> &modelController,
                                             const std::shared_ptr<FilesController> &filesController,
                                             const QVariant &data)
            : Process(data),
            m_modelController(modelController),
            m_filesController(filesController) {

}

QVariantMap RelationRemoveProcess::modelData(const QVariant &data) const {
    return {
        { "playlist", data.toMap().value("playlist") },
        { "song", data.toMap().value("song") },
    };
}

void RelationRemoveProcess::start() {
    if (not inputData().toMap().isEmpty()) {
        m_modelController->removeData(modelData(inputData()), RELATIONS);
    }
}
