#ifndef PENDABLEPROCESS_H
#define PENDABLEPROCESS_H

#include "process.h"

#include "../controllers/modelcontroller.h"

#include <memory>

#include <QObject>
#include <QVariant>

class PendableProcess : public Process {
public:
    PendableProcess(const QVariant &inputData, const std::shared_ptr<ModelController> &modelController);

    void finishPending();

    QVariantMap pendingModelData() const;
    QVariantMap pendingFinishedModelData() const;

private:
    std::shared_ptr<ModelController> m_modelController;
};

#endif // PENDABLEPROCESS_H
