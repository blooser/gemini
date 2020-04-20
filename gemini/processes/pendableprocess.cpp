#include "pendableprocess.h"

namespace  {
    constexpr Enums::Data PENDING = Enums::Data::Pending;
    constexpr int DONE = 1;
}

PendableProcess::PendableProcess(const QVariant &inputData, const std::shared_ptr<ModelController> &modelController)
    : Process(inputData),
      m_modelController(modelController) {

}

QVariantMap PendableProcess::pendingModelData() const {
    return {
        { "url", inputData().toUrl() }
    };
}

QVariantMap PendableProcess::pendingFinishedModelData() const {
    return {
        { "url", inputData().toUrl() },
        { "name", inputData().toUrl().fileName() },
        { "done", DONE }
    };
}

void PendableProcess::finishPending() {
    m_modelController->updateData(pendingModelData(), pendingFinishedModelData(), PENDING);
}
