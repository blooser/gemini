#include "databasecontroller.h"
#include "../database/databasetables.h"
#include "../paths/paths.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>

Q_LOGGING_CATEGORY(databaseController, "database.controller")

namespace {
    const QString DB_NAME = QStringLiteral("local.db");
    const QString CONNECTION = QStringLiteral("gemini");
}

DatabaseController::DatabaseController(const QString &m_appPath, QObject *parent)
    : QObject(parent),
      m_dbPath(paths::join(m_appPath, DB_NAME)){

    if (!databaseExists()) {
        qCInfo(databaseController) << "Creating database";

        if (!createPathDir()) {
            qCCritical(databaseController) << "Could not create database";
        }

        openDatabase();
        fillDatabase();
    } else {
        if (!openDatabase()) {
            qCCritical(databaseController) << "Failed to open database";
        }
    }
}

QString DatabaseController::databasePath() const {
    return m_dbPath;
}

QString DatabaseController::connectionName() const {
    return m_database.connectionName();
}

QSqlDatabase DatabaseController::database() {
    return m_database;
}

bool DatabaseController::databaseExists() {
    return QFileInfo::exists(m_dbPath);
}

bool DatabaseController::createPathDir() {
    return QFileInfo(m_dbPath).absoluteDir().mkpath(".");
}

bool DatabaseController::databaseIsOpen() {
    return m_database.isOpen();
}

bool DatabaseController::openDatabase() {
    database::core::setup(m_database, m_dbPath, CONNECTION);
    return m_database.isOpen();
}

void DatabaseController::fillDatabase() {
    for (auto &pragma : database::Pragmas) {
        pragma(m_database);
    }

    for (auto &table : database::Tables) {
        table(m_database);
    }

    for (auto &trigger : database::Triggers) {
        trigger(m_database);
    }
}
