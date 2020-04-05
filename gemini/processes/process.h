#ifndef PROCESS_H
#define PROCESS_H

#include <QVariant>

class Process {
public:
    explicit Process(const QVariant &inputData);

    QVariant inputData() const;

    virtual QVariantMap modelData(const QVariant &data) const = 0;
    virtual void start() = 0;

private:
    QVariant m_inputData;
};

#endif // PROCESS_H
