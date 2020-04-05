#ifndef PENDINGPROCESS_H
#define PENDINGPROCESS_H

#include "../process.h"

#include "../../common/enums.h"
#include "../../controllers/modelcontroller.h"

#include <memory>

#include <QObject>

class PendingInsertProcess : public Process {
public:
    PendingInsertProcess(const std::shared_ptr<ModelController> &modelController,
                         const QVariant &data);

    QVariantMap modelData(const QVariant &data) const override;
    void start() override;

private:
    std::shared_ptr<ModelController> m_modelController;
};

#endif // PENDINGPROCESS_H
