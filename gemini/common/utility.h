#ifndef UTILITY_H
#define UTILITY_H

#include "enums.h"

#include <QObject>
#include <QMetaEnum>
#include <QString>

class Utility : public QObject {
    Q_OBJECT

public:
    static Utility &instance();

    template <typename Enum>
    static QString enumToString(const Enum enumValue) {
        return QMetaEnum::fromType<Enum>().valueToKey(static_cast<int>(enumValue));
    }

    static bool isPendable(Enums::Data data);

    Q_INVOKABLE static QString formatTime(const int ms, const QString &format);
    Q_INVOKABLE static int msFromString(const QString &string, const QString &format);
    Q_INVOKABLE static QString fileSize(const QUrl &url);

private:
    Utility(QObject *parent=nullptr);
};

#endif // UTILITY_H
