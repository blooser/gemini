#ifndef PLAYLISTREMOVEPROCESS_H
#define PLAYLISTREMOVEPROCESS_H

#include "../process.h"

#include "../../controllers/filescontroller.h"
#include "../../controllers/modelcontroller.h"

#include <memory>

#include <QObject>

class PlaylistRemoveProcess : public Process {
public:
    PlaylistRemoveProcess(const std::shared_ptr<ModelController> &modelController,
                          const QVariant &data);

    QVariantMap modelData(const QVariant &data) const override;
    void start() override;

protected:
    QVariantMap relationsModelData(const QVariant &data) const;

private:
    std::shared_ptr<ModelController> m_modelController;
};

#endif // PLAYLISTREMOVEPROCESS_H
