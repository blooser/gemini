#ifndef PENDINGDELETEPROCESS_H
#define PENDINGDELETEPROCESS_H

#include "../process.h"

#include "../../common/enums.h"
#include "../../controllers/modelcontroller.h"

#include <memory>

#include <QObject>

class PendingRemoveProcess : public Process {
public:
    PendingRemoveProcess(const std::shared_ptr<ModelController> &modelController);

    QVariantMap modelData(const QVariant &data) const override;
    void start() override;

private:
    std::shared_ptr<ModelController> m_modeController;
};

#endif // PENDINGDELETEPROCESS_H
