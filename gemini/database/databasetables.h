#ifndef DATABASETABLES_H
#define DATABASETABLES_H

#include "databasecore.h"

#include <functional>

#include <QString>
#include <QVector>

namespace database {

extern const QVector<std::function<bool (const QSqlDatabase&)>> Tables {
        std::bind(qOverload<const QSqlDatabase &, const QLatin1String &>(&database::core::run), std::placeholders::_1, QLatin1String("CREATE TABLE wallpapers ("
                                                                                                                                     "`id` INTEGER PRIMARY KEY,"
                                                                                                                                     "`url` TEXT NOT NULL UNIQUE"
                                                                                                                                     ")")),

        std::bind(qOverload<const QSqlDatabase &, const QLatin1String &>(&database::core::run), std::placeholders::_1, QLatin1String("CREATE TABLE playlists ("
                                                                                                                                     "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
                                                                                                                                     "`name` TEXT NOT NULL UNIQUE,"
                                                                                                                                     "`songs` INTEGER DEFAULT 0,"
                                                                                                                                     "`duration` INTEGER DEFAULT 0"
                                                                                                                                     ")")),

        std::bind(qOverload<const QSqlDatabase &, const QLatin1String &>(&database::core::run), std::placeholders::_1, QLatin1String("CREATE TABLE songs ("
                                                                                                                                     "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
                                                                                                                                     "`title` TEXT NOT NULL,"
                                                                                                                                     "`artist` TEXT,"
                                                                                                                                     "`album` TEXT,"
                                                                                                                                     "`genre` TEXT,"
                                                                                                                                     "`year` INTEGER,"
                                                                                                                                     "`duration` INTEGER NOT NULL CHECK(duration>0),"
                                                                                                                                     "`completed` INTEGER DEFAULT 0,"
                                                                                                                                     "`url` TEXT NOT NULL UNIQUE"
                                                                                                                                     ")")),

        std::bind(qOverload<const QSqlDatabase &, const QLatin1String &>(&database::core::run), std::placeholders::_1, QLatin1String("CREATE TABLE relations ("
                                                                                                                                     "`playlist` INTEGER NOT NULL,"
                                                                                                                                     "`song` INTEGER NOT NULL,"
                                                                                                                                     "FOREIGN KEY(playlist) references playlists(id),"
                                                                                                                                     "FOREIGN KEY(song) references songs(id)"
                                                                                                                                     ")")),

        std::bind(qOverload<const QSqlDatabase &, const QLatin1String &>(&database::core::run), std::placeholders::_1, QLatin1String("CREATE TABLE pending ("
                                                                                                                                     "`url` TEXT NOT NULL UNIQUE,"
                                                                                                                                     "`done` INTEGER DEFAULT 0"
                                                                                                                                     ")"))
    };
}


#endif // DATABASETABLES_H
