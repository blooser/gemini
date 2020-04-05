#include "databasecore.h"

#include <QSqlError>

#include <QLoggingCategory>
Q_LOGGING_CATEGORY(databaseCore, "database.core")

const QString database::core::DB_TYPE = QStringLiteral("QSQLITE");

void database::core::setup(QSqlDatabase &database, const QString databasePath, const QString &connectionName) {
     database = QSqlDatabase::addDatabase(DB_TYPE, connectionName);
     database.setDatabaseName(databasePath);

     if (!database.open()) {
        qCCritical(databaseCore) << "Could not open database";
     }
}

QSqlDatabase database::core::database(const QString &connectionName) {
    if (!exists(connectionName)) {
        qCCritical(databaseCore) << "Database connection [" << connectionName << "] doesn't exists";
    }

    return QSqlDatabase::database(connectionName);
}

bool database::core::exists(const QString &connectionName) {
    return QSqlDatabase::contains(connectionName);
}

bool database::core::error(const QSqlQuery &query) {
    return query.lastError().isValid();
}
void database::core::run(QSqlQuery &query) {
    query.exec();
    if (error(query)) {
        qCCritical(databaseCore) << "Cannot run query [ " << query.lastError().text() << " ]";
    }
}

bool database::core::run(const QSqlDatabase &database, const QLatin1String &msg) {
    auto query = QSqlQuery(database);
    query.prepare(msg);
    run(query);
    return  !error(query);
}
