#include "pendingremoveprocess.h"

namespace {
    constexpr Enums::Data PENDING = Enums::Data::Pending;
}

PendingRemoveProcess::PendingRemoveProcess(const std::shared_ptr<ModelController> &modelController)
    : Process(QVariant()),
      m_modeController(modelController) {

}

QVariantMap PendingRemoveProcess::modelData(const QVariant &) const {
    return QVariantMap();
}

void PendingRemoveProcess::start() {
    m_modeController->erase(PENDING);
}

