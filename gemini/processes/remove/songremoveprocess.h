#ifndef SONGREMOVEPROCESS_H
#define SONGREMOVEPROCESS_H

#include "../process.h"

#include "../../controllers/filescontroller.h"
#include "../../controllers/modelcontroller.h"

#include <memory>

#include <QObject>

class SongRemoveProcess : public Process {
public:
    SongRemoveProcess(const std::shared_ptr<ModelController> &modelController,
                      const std::shared_ptr<FilesController> &filesController,
                      const QVariant &data);

    QVariantMap modelData(const QVariant &data) const override;
    void start() override;

protected:
    QVariantMap relationsModelData(const QVariant &data) const;

private:
    std::shared_ptr<ModelController> m_modelController;
    std::shared_ptr<FilesController> m_filesController;
};

#endif // SONGREMOVEPROCESS_H
