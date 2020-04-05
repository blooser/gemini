#include "process.h"

Process::Process(const QVariant &inputData)
    : m_inputData(inputData) {

}

QVariant Process::inputData() const {
    return m_inputData;
}
