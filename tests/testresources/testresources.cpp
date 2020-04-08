#include <QByteArray>
#include <QString>
#include <QFile>

namespace testresources {

QByteArray read(const QString &path) {
    QFile file(path);

    if (not file.open(QIODevice::ReadOnly)) {
        return QByteArray();
    }

    auto bytes = file.readAll();
    file.close();
    return bytes;
};

}
