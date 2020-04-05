#ifndef DatabaseController_H
#define DatabaseController_H

#include "../database/databasecore.h"

#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(databaseController)

class DatabaseController : public QObject {
    Q_OBJECT

public:
    explicit DatabaseController(const QString &m_appPath, QObject *parent = nullptr);

    QString databasePath() const;
    QString connectionName() const;
    QSqlDatabase database();

private:
    const QString m_dbPath;
    QSqlDatabase m_database;

    bool databaseExists();
    bool createPathDir();
    bool openDatabase();
    void fillDatabase();
    bool databaseIsOpen();
};

#endif // DatabaseController_H
