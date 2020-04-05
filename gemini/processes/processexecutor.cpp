#include "processexecutor.h"

Q_LOGGING_CATEGORY(processExecutor, "process.executor")

ProcessExecutor::ProcessExecutor(QObject *parent)
    : QThread(parent) {

    setupConnections();
}

void ProcessExecutor::run() {
    qCInfo(processExecutor) << "Running" << m_processes.size() << "process(es)";

    for (const auto &process : qAsConst(m_processes)) {
        process->start();
    }

    m_processes.clear();
}

void ProcessExecutor::appendProcess(const std::shared_ptr<Process> &process) {
    m_processes.append(process);
}

void ProcessExecutor::prependProcess(const std::shared_ptr<Process> &process) {
    m_processes.prepend(process);
}

void ProcessExecutor::setupConnections() {
    connect(this, &ProcessExecutor::started,
            this, std::bind(&ProcessExecutor::processingChanged, this, true));
    connect(this, &ProcessExecutor::finished,
            this, std::bind(&ProcessExecutor::processingChanged, this, false));
}

