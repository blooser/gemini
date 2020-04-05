#include "playlistmodel.h"
#include "../database/databasecore.h"

#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>

Q_LOGGING_CATEGORY(playlistModel, "playlist.model")

const QHash<int, QByteArray> PlaylistModel::ROLE_NAMES {
    { Column::Id, QByteArrayLiteral("id") },
    { Column::Name, QByteArrayLiteral("name") }
};

const QHash<int, QMetaType::Type> PlaylistModel::DATA_TYPES {
    { Column::Id, QMetaType::Int },
    { Column::Name, QMetaType::QString}
};

PlaylistModel::PlaylistModel(QSqlDatabase &db, QObject *parent)
    : SqlTableModel(db, "playlists", parent) {

}

int PlaylistModel::firstColumn() const {
    return columnShift(Column::Id);
}

int PlaylistModel::lastColumn() const {
    return columnShift(Column::Last);
}

QHash<int, QByteArray> PlaylistModel::roleNames() const {
    return ROLE_NAMES;
}

QHash<int, QMetaType::Type>  PlaylistModel::dataTypes() const {
    return DATA_TYPES;
}
