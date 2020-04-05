#ifndef READMODEL_H
#define READMODEL_H

#include "../sqltablemodel.h"

#include <QSqlRecord>

#include <QObject>
#include <QAbstractProxyModel>

class ReadModel : public QAbstractProxyModel {
    Q_OBJECT
    Q_PROPERTY(int size READ rowCount NOTIFY sizeChanged)

public:
    ReadModel(QObject *parent=nullptr);

    void setSourceModel(SqlTableModel *newSourceModel);

    int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    int columnCount(const QModelIndex&) const override;

    QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QModelIndex index(int, int, const QModelIndex&) const override;
    QModelIndex parent(const QModelIndex&) const override;

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;

signals:
    void sizeChanged(const int size);

private slots:
    void sourceRowsInserted(const QModelIndex &parent, int start, int end);
    void sourceRowsRemoved(const QVector<int> &rows);
    void sourceModelErased();

    void updateSize();

private:
    using QAbstractProxyModel::setSourceModel;
};

#endif // READMODEL_H
