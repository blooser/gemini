#include "wallpaperremoveprocess.h"

namespace {
    constexpr Enums::Data WALLPAPERS = Enums::Data::Wallpapers;
}

WallpaperRemoveProcess::WallpaperRemoveProcess(const std::shared_ptr<ModelController> &modelController,
                                               const std::shared_ptr<FilesController> &filesController,
                                               const QVariant &data)
              : Process(data),
              m_modelController(modelController),
              m_filesController(filesController) {

}

QVariantMap WallpaperRemoveProcess::modelData(const QVariant &data) const {
    return {
        { "id", data.toMap().value("id").toInt() }
    };
}

void WallpaperRemoveProcess::start() {
    if (not inputData().toMap().isEmpty()) {
        m_filesController->remove(inputData().toMap().value("url").toUrl().path());
        m_modelController->removeData(modelData(inputData()), WALLPAPERS);
    }
}
