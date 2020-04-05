#ifndef WALLPAPERREMOVEPROCESS_H
#define WALLPAPERREMOVEPROCESS_H

#include "../process.h"

#include "../../controllers/filescontroller.h"
#include "../../controllers/modelcontroller.h"

#include <memory>

#include <QObject>

class WallpaperRemoveProcess : public Process {
public:
    WallpaperRemoveProcess(const std::shared_ptr<ModelController> &modelController,
                           const std::shared_ptr<FilesController> &filesController,
                           const QVariant &data);

    QVariantMap modelData(const QVariant &data) const override;
    void start() override;

private:
    std::shared_ptr<ModelController> m_modelController;
    std::shared_ptr<FilesController> m_filesController;
};

#endif // WALLPAPERREMOVEPROCESS_H
