#include "pendingmodel.h"

const QHash<int, QByteArray> PendingModel::ROLE_NAMES {
    { Column::Url, QByteArrayLiteral("url") },
    { Column::Name, QByteArrayLiteral("name") },
    { Column::Done, QByteArrayLiteral("done") }
};

const QHash<int, QMetaType::Type> PendingModel::DATA_TYPES {
    { Column::Url, QMetaType::QString },
    { Column::Name, QMetaType::QString },
    { Column::Done, QMetaType::Bool }
};

PendingModel::PendingModel(QSqlDatabase &db, QObject *parent)
    : SqlTableModel(db, "pending", parent){

}

int PendingModel::firstColumn() const {
    return columnShift(Column::Url);
}

int PendingModel::lastColumn() const {
    return columnShift(Column::Last);
}

QHash<int, QByteArray> PendingModel::roleNames() const {
    return ROLE_NAMES;
}

QHash<int, QMetaType::Type>  PendingModel::dataTypes() const {
    return DATA_TYPES;
}

