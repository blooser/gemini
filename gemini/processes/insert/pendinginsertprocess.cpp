#include "pendinginsertprocess.h"

namespace {
    constexpr Enums::Data PENDING = Enums::Data::Pending;
}

PendingInsertProcess::PendingInsertProcess(const std::shared_ptr<ModelController> &modelController,
                               const QVariant &data)
    : Process(data),
      m_modelController(modelController) {

}

QVariantMap PendingInsertProcess::modelData(const QVariant &data) const {
    return {
        { "url", data.toUrl().path() },
        { "done", 0 }
    };
}

void PendingInsertProcess::start() {
    auto urls = inputData().toList();
    for (const auto &url : urls) {
        if (url.toUrl().isValid()) {
            m_modelController->appendData(modelData(url), PENDING);
        }
    }
}
