#include "wallpaperinsertprocess.h"

#include "../../common/enums.h"

namespace {
    constexpr Enums::Data WALLPAPERS = Enums::Data::Wallpapers;
}

WallpaperInsertProcess::WallpaperInsertProcess(const std::shared_ptr<ModelController> &modelController,
                                   const std::shared_ptr<FilesController> &filesController,
                                   const QVariant &data)
    : PendableProcess(data, modelController),
      m_modelController(modelController),
      m_filesController(filesController) {

}

QVariantMap WallpaperInsertProcess::modelData(const QVariant &data) const {
    return {
        { "name", data.toUrl().fileName() },
        { "url", data.toUrl() }
    };
}

void WallpaperInsertProcess::start() {
    auto newUrl = m_filesController->put(inputData().toUrl(), WALLPAPERS);
    if (not newUrl.isEmpty()) {
        m_modelController->appendData(modelData(newUrl), WALLPAPERS);
        finishPending();
    }
}
