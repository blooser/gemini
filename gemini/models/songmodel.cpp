#include "songmodel.h"

#include <QUrl>
#include <QSqlRecord>
#include <QSqlField>
#include <QFileInfo>

Q_LOGGING_CATEGORY(songModel, "song.model")

const QHash<int, QByteArray> SongModel::ROLE_NAMES {
    { Column::Id, QByteArrayLiteral("id") },
    { Column::Name, QByteArrayLiteral("name") },
    { Column::Url, QByteArrayLiteral("url") }
};

const QHash<int, QMetaType::Type> SongModel::DATA_TYPES {
    { Column::Id, QMetaType::Int },
    { Column::Name, QMetaType::QString },
    { Column::Url, QMetaType::QUrl }
};

SongModel::SongModel(QSqlDatabase &db, QObject *parent)
    : SqlTableModel(db, "songs", parent)
{

}

int SongModel::firstColumn() const {
    return columnShift(Column::Id);
}

int SongModel::lastColumn() const {
    return columnShift(Column::Last);
}

QHash<int, QByteArray> SongModel::roleNames() const {
    return ROLE_NAMES;
}

QHash<int, QMetaType::Type> SongModel::dataTypes() const {
    return DATA_TYPES;
}
