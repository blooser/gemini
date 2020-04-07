#ifndef FILESCONTROLLER_H
#define FILESCONTROLLER_H

#include "../common/enums.h"

#include <QObject>
#include <QString>
#include <QUrl>
#include <QHash>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(filesController)

class FilesController : public QObject {
    Q_OBJECT

public:
    explicit FilesController(const QString &corePath, QObject *parent = nullptr);

    QUrl put(const QUrl &url, Enums::Data data);
    QUrl generateUrl(const QUrl &url, Enums::Data data);
    void remove(const QUrl &url);

    QString path() const;
    QStringList subdirectories() const;

private:
    const QString m_corePath;
    bool directoryExists(const QString &path);
    bool fileExists(const QString &path);
    void createDirectories();
};

#endif // FILESCONTROLLER_H
