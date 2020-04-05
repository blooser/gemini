#ifndef PROCESSEXECUTOR_H
#define PROCESSEXECUTOR_H

#include "process.h"

#include <QThread>
#include <QVector>

#include <memory>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(processExecutor)

class ProcessExecutor : public QThread {
    Q_OBJECT

public:
    ProcessExecutor(QObject *parent=nullptr);

    void appendProcess(const std::shared_ptr<Process> &process);
    void prependProcess(const std::shared_ptr<Process> &process);

signals:
    void processingChanged(const bool &processing);

protected:
    void run() override;

private:
    QVector<std::shared_ptr<Process>> m_processes;

    void setupConnections();
};

#endif // PROCESSEXECUTOR_H
