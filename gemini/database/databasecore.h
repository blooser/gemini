#ifndef DATABASECORE_H
#define DATABASECORE_H

#include <QSqlDatabase>
#include <QSqlQuery>

namespace database {
namespace core {
    extern const QString DB_TYPE;
    void setup(QSqlDatabase &database, const QString databasePath, const QString &connectionName);
    QSqlDatabase database(const QString &connectionName);
    bool exists(const QString &connectionName);
    void run(QSqlQuery &query);
    bool run(const QSqlDatabase &database, const QLatin1String &msg);
    bool error(const QSqlQuery &query);
}
}

#endif // DATABASECORE_H
