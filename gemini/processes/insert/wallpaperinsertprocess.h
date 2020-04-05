#ifndef WALLPAPERPROCESS_H
#define WALLPAPERPROCESS_H

#include "../pendableprocess.h"

#include "../../controllers/filescontroller.h"
#include "../../controllers/modelcontroller.h"

#include <memory>

#include <QObject>

class WallpaperInsertProcess : public PendableProcess {
public:
    WallpaperInsertProcess(const std::shared_ptr<ModelController> &modelController,
                           const std::shared_ptr<FilesController> &filesController,
                           const QVariant &data);

    QVariantMap modelData(const QVariant &data) const override;
    void start() override;

private:
    std::shared_ptr<ModelController> m_modelController;
    std::shared_ptr<FilesController> m_filesController;
};

#endif // WALLPAPERPROCESS_H
