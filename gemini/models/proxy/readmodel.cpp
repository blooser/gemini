#include "readmodel.h"

#include <QModelIndex>

ReadModel::ReadModel(QObject *parent)
    : QAbstractProxyModel(parent) {

}

int ReadModel::rowCount(const QModelIndex &) const {
    return sourceModel()->rowCount(QModelIndex());
}

int ReadModel::columnCount(const QModelIndex &) const {
    return sourceModel()->roleNames().size();
}

QVariant ReadModel::data(const QModelIndex &proxyIndex, int role) const {
    return sourceModel()->data(mapToSource(proxyIndex), role);
}

QHash<int, QByteArray> ReadModel::roleNames() const {
    return sourceModel()->roleNames();
}

QModelIndex ReadModel::index(int row, int column, const QModelIndex &) const {
    return sourceModel()->index(row, column);
}

QModelIndex ReadModel::parent(const QModelIndex &) const {
    return QModelIndex();
}

QModelIndex ReadModel::mapToSource(const QModelIndex &proxyIndex) const {
    if (not proxyIndex.isValid()) {
        return QModelIndex();
    }

   return sourceModel()->index(proxyIndex.row(), proxyIndex.column());
}

QModelIndex ReadModel::mapFromSource(const QModelIndex &sourceIndex) const {
    if (not sourceIndex.isValid()) {
        return QModelIndex();
    }

    return sourceModel()->index(sourceIndex.row(), sourceIndex.column());
}

void ReadModel::updateSize() {
    emit sizeChanged(rowCount());
}

void ReadModel::setSourceModel(SqlTableModel *newSourceModel) {
    if (sourceModel()) {
        disconnect(dynamic_cast<SqlTableModel*>(sourceModel()), &QSqlTableModel::rowsInserted,
                   this, &ReadModel::sourceRowsInserted);
        disconnect(dynamic_cast<SqlTableModel*>(sourceModel()), &SqlTableModel::rowsRemoved,
                   this, &ReadModel::sourceRowsRemoved);
        disconnect(dynamic_cast<SqlTableModel*>(sourceModel()), &SqlTableModel::erased,
                   this, &ReadModel::sourceModelErased);
        disconnect(sourceModel(), &QAbstractItemModel::dataChanged,
                   this, &ReadModel::dataChanged);

    }

    QAbstractProxyModel::setSourceModel(newSourceModel);

    if (newSourceModel) {
        connect(dynamic_cast<SqlTableModel*>(sourceModel()), &QSqlTableModel::rowsInserted,
                   this, &ReadModel::sourceRowsInserted);
        connect(dynamic_cast<SqlTableModel*>(sourceModel()), &SqlTableModel::rowsRemoved,
                   this, &ReadModel::sourceRowsRemoved);
        connect(dynamic_cast<SqlTableModel*>(sourceModel()), &SqlTableModel::erased,
                   this, &ReadModel::sourceModelErased);
        connect(sourceModel(), &QAbstractItemModel::dataChanged,
                   this, &ReadModel::dataChanged);

    }
}

void ReadModel::sourceModelErased() {
    beginResetModel();
    endResetModel();

    updateSize();
}

void ReadModel::sourceRowsInserted(const QModelIndex &, int start, int end) {
    beginInsertRows(QModelIndex(), start, end);
    endInsertRows();

    updateSize();
}

void ReadModel::sourceRowsRemoved(const QVector<int> &rows) {
    for (const auto &row : rows) {
        beginRemoveRows(QModelIndex(), row, row);
        endRemoveRows();
    }

    updateSize();
}
