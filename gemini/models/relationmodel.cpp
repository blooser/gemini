#include "relationmodel.h"

Q_LOGGING_CATEGORY(relationModel, "relation.model")

const QHash<int, QByteArray> RelationModel::ROLE_NAMES {
    { Column::Playlist, QByteArrayLiteral("playlist") },
    { Column::Song, QByteArrayLiteral("song") }
};

const QHash<int, QMetaType::Type> RelationModel::DATA_TYPES {
    { Column::Playlist, QMetaType::Int },
    { Column::Song, QMetaType::Int }
};

RelationModel::RelationModel(QSqlDatabase &db, QObject *parent)
    : SqlTableModel(db, "relations", parent) {

}

int RelationModel::firstColumn() const {
    return columnShift(Column::Playlist);
}

int RelationModel::lastColumn() const {
    return columnShift(Column::Last);
}

QHash<int, QByteArray> RelationModel::roleNames() const {
    return ROLE_NAMES;
}

QHash<int, QMetaType::Type> RelationModel::dataTypes() const {
    return DATA_TYPES;
}

