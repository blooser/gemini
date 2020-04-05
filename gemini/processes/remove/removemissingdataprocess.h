#ifndef REMOVEMISSINGDATAPROCESS_H
#define REMOVEMISSINGDATAPROCESS_H

#include "../process.h"

#include "../../controllers/modelcontroller.h"

#include <QAbstractItemModel>

class RemoveMissingDataProcess : public Process {
public:
    RemoveMissingDataProcess(const std::shared_ptr<ModelController> &modelController);

    QVariantMap modelData(const QVariant &data) const override;
    void start() override;

private:
    std::shared_ptr<ModelController> m_modelController;

    QVector<QUrl> collectMissing(Enums::Data data);
};

#endif // REMOVEMISSINGDATAPROCESS_H
