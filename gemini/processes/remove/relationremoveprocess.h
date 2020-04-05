#ifndef RELATIONREMOVEPROCESS_H
#define RELATIONREMOVEPROCESS_H

#include "../process.h"

#include "../../controllers/filescontroller.h"
#include "../../controllers/modelcontroller.h"

#include <memory>

#include <QObject>

class RelationRemoveProcess : public Process {  
public:
    RelationRemoveProcess(const std::shared_ptr<ModelController> &modelController,
                          const std::shared_ptr<FilesController> &filesController,
                          const QVariant &data);

    QVariantMap modelData(const QVariant &data) const override;
    void start() override;

private:
    std::shared_ptr<ModelController> m_modelController;
    std::shared_ptr<FilesController> m_filesController;
};

#endif // RELATIONREMOVEPROCESS_H
