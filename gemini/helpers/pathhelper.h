#ifndef PATHHELPER_H
#define PATHHELPER_H

#include <QString>

class PathHelper {
public:
    template <typename ...Paths>
    static QString join(const QString &root, Paths ...paths) {
        return (root + ... + (QStringLiteral("/") + QString(paths)));
    }
};

#endif // PATHHELPER_H
