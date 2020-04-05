#ifndef PLAYLISTPROCESS_H
#define PLAYLISTPROCESS_H

#include "../process.h"

#include "../../common/enums.h"
#include "../../controllers/filescontroller.h"
#include "../../controllers/modelcontroller.h"

#include <memory>

#include <QObject>
#include <QVector>

class PlaylistInsertProcess : public Process {
public:
    PlaylistInsertProcess(const std::shared_ptr<ModelController> &modelController,
                          const QVariant &data);

    QVariantMap modelData(const QVariant &data) const override;
    void start() override;

private:
    std::shared_ptr<ModelController> m_modelController;
};

#endif // PLAYLISTPROCESS_H
