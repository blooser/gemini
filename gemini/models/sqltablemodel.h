#ifndef SQLTABLEMODEL_H
#define SQLTABLEMODEL_H

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QHash>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(sqlTableModel)

class SqlTableModel : public QSqlTableModel {
    Q_OBJECT

public:
    explicit SqlTableModel(QSqlDatabase &database, const QString &table, QObject *parent = nullptr);

    virtual int firstColumn() const = 0;
    virtual int lastColumn() const = 0;

    virtual QHash<int, QMetaType::Type> dataTypes() const = 0;

    void append(const QVariantMap &modelData);
    void remove(const QVariantMap &modelData);
    QVariantList read(const QByteArray &roleName) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void updateData(const QVariantMap &searechModelData, const QVariantMap &modelData);
    bool erase();

    QVariantList findBuddy(const QVariantMap &modelData, const QByteArray &roleName, int hints=1);
    QModelIndexList find(const QVariantMap &modelData, int hints=-1);

    int roleShift(const int column) const;
    int columnShift(const int role) const;

signals:
    void rowsRemoved(const QVector<int> &rows);
    void erased();

protected:
    QSqlRecord prepareRecord(const QVariantMap &modelData);
};

#endif // SQLMODEL_H
