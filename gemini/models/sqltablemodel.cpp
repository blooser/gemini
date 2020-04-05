#include "sqltablemodel.h"

#include "../database/databasecore.h"

#include <QSqlError>
#include <QSqlField>
#include <QSqlRecord>

#include <QLoggingCategory>
Q_LOGGING_CATEGORY(sqlTableModel, "sql.table.model")

SqlTableModel::SqlTableModel(QSqlDatabase &database, const QString &table, QObject *parent) : QSqlTableModel(parent, database) {
    setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);
    setTable(table);
    select();

    qCInfo(sqlTableModel) << "Prepare" << tableName() << "number of rows:" << rowCount();
}

int SqlTableModel::roleShift(const int column) const {
    return column + Qt::UserRole + 1;
}

int SqlTableModel::columnShift(const int role) const {
    return role - Qt::UserRole - 1;
}

QVariant SqlTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::EditRole) {
        return QSqlTableModel::data(index, role);
    }

    QModelIndex m_index = this->index(index.row(), columnShift(role), index.parent());
    return QSqlTableModel::data(m_index);
}

void SqlTableModel::updateData(const QVariantMap &searechModelData, const QVariantMap &modelData) {
    auto record = prepareRecord(modelData);

    for (auto &index : find(searechModelData)) {
        setRecord(index.row(), record);
    }

    if (!submitAll()) {
        qCWarning(sqlTableModel) << "Submit failed!" << lastError().text();
    }
}

bool SqlTableModel::erase() {
    if (rowCount() == 0) {
        qCWarning(sqlTableModel) << "Trying to erase empty model!";
        return false;
    }

    const QString deleteQueryString = QString("DELETE FROM %1").arg(tableName());

    QSqlQuery deleteQuery(database());
    deleteQuery.prepare(deleteQueryString);

    database::core::run(deleteQuery);

    select();

    emit erased();

    return !database::core::error(deleteQuery);
}

QModelIndexList SqlTableModel::find(const QVariantMap &modelData, int hints) {
    const int numberOfKeys = modelData.size();

    QMap<int, int> rowHistogram = {};
    QModelIndexList foundIndexes = {};
    for (const auto &key : modelData.keys()) {
        auto role = roleNames().key(key.toUtf8());
        auto indexes = match(createIndex(0, 0), role, modelData.value(key), hints, Qt::MatchExactly);

        for (const auto &index : qAsConst(indexes)) {
            ++rowHistogram[index.row()];

            if (rowHistogram[index.row()] == numberOfKeys) {
                foundIndexes.append(index);
            }
        }
    }

    return foundIndexes;
}

QVariant SqlTableModel::findBuddy(const QVariantMap &modelData, const QByteArray &roleName) {
    auto indexes = find(modelData, 1);

    if (!indexes.isEmpty()) {
        auto back = indexes.back();
        if (back.isValid()) {
            return data(back, roleNames().key(roleName));
        }
    }

    return QVariant();
}

void SqlTableModel::append(const QVariantMap &modelData) {
    if (not find(modelData).isEmpty()) {
        return;
    }

    auto record = prepareRecord(modelData);

    if (!insertRecord(rowCount(), record)) {
        qCWarning(sqlTableModel) << "Insert record failed!";
    }

    if (!submitAll()) {
        qCWarning(sqlTableModel) << "Submit failed!" << lastError().text();
    }
}

void SqlTableModel::remove(const QVariantMap &modelData) {
    QVector<int> rows;

    for (const auto &index : find(modelData)) {
        removeRow(index.row());
        rows.append(index.row());
    }

    if (!submitAll()) {
        qCWarning(sqlTableModel) << "Submit failed!" << lastError().text();
        return;
    }

    emit rowsRemoved(rows);
}

QVariantList SqlTableModel::read(const QByteArray &roleName) const {
    QVariantList collectedData;
    for (int i=0; i<rowCount(); ++i) {
        auto currentIndex = index(i, 0);
        auto role = roleNames().key(roleName);
        collectedData.append(data(currentIndex, role));
    }

    return collectedData;
}

QSqlRecord SqlTableModel::prepareRecord(const QVariantMap &modelData) {
    QSqlRecord record;
    for (auto column = firstColumn(); column < lastColumn(); ++column) {
        record.append(QSqlField{roleNames().value(roleShift(column)), static_cast<QVariant::Type>(dataTypes().value(roleShift(column)))});
    }

    for (const auto &key : modelData.keys()) {
        record.setValue(key, modelData.value(key));
    }

    return record;
}
