#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include "../common/enums.h"

#include <QObject>
#include <QUrl>
#include <QVariantMap>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(objectController)

class ObjectController : public QObject {
    Q_OBJECT

public:
    explicit ObjectController(QObject *parent = nullptr);

    Q_INVOKABLE void openDialog(Enums::Dialog dialog, const QVariantMap &properties, const QVariant &callback);

signals:
    void open(const QString &url, const QVariantMap &properties, const QVariant &callback);
    void close(const Enums::Dialog dialog);

private:
    QString path(Enums::Dialog dialog);
};

#endif // OBJECTCONTROLLER_H
