#ifndef RESUMEUNFINISHEDPENDINGPROCESS_H
#define RESUMEUNFINISHEDPENDINGPROCESS_H

#include "../process.h"

#include "../../common/enums.h"

#include "../../controllers/modelcontroller.h"
#include "../../controllers/filescontroller.h"

class ResumeUnfinishedPendingProcess : public Process {
public:
    ResumeUnfinishedPendingProcess(const std::shared_ptr<ModelController> &modelController,
                                   const std::shared_ptr<FilesController> &filesController);

    QVariantMap modelData(const QVariant &data) const override;
    void start() override;

private:
    std::shared_ptr<ModelController> m_modelController;
    std::shared_ptr<FilesController> m_filesController;

    QVector<QUrl> collectUrls() const;
    std::shared_ptr<Process> createInsertProcessByUrl(const QUrl &url);
    QVector<std::shared_ptr<Process>> createInsertProcesses();

    void pendingFinished();
};

#endif // RESUMEUNFINISHEDPENDINGPROCESS_H
