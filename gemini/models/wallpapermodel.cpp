#include "wallpapermodel.h"
#include "sqltablemodel.h"
#include "../database/databasecore.h"

#include <QSqlRecord>
#include <QSqlError>
#include <QSqlField>
#include <QUrl>
#include <QFileInfo>

Q_LOGGING_CATEGORY(wallpaperModel, "wallpaper.model")

const QHash<int, QByteArray> WallpaperModel::ROLE_NAMES {
    { Column::Id, QByteArrayLiteral("id") },
    { Column::Url, QByteArrayLiteral("url") },
};

const QHash<int, QMetaType::Type> WallpaperModel::DATA_TYPES {
    { Column::Id, QMetaType::Int },
    { Column::Url, QMetaType::QUrl}
};

WallpaperModel::WallpaperModel(QSqlDatabase &db, QObject *parent)
    : SqlTableModel(db, "wallpapers", parent) {

}

int WallpaperModel::firstColumn() const {
    return columnShift(Column::Id);
}

int WallpaperModel::lastColumn() const {
    return columnShift(Column::Last);
}

QHash<int, QByteArray> WallpaperModel::roleNames() const {
    return ROLE_NAMES;
}

QHash<int, QMetaType::Type> WallpaperModel::dataTypes() const {
    return DATA_TYPES;
}
