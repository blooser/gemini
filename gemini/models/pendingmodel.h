#ifndef PENDINGMODEL_H
#define PENDINGMODEL_H

#include "sqltablemodel.h"

#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(pendingModel)

class PendingModel : public SqlTableModel {
    Q_OBJECT

public:
    enum Column {
        Url = Qt::UserRole + 1,
        Done,

        Last
    };

    explicit PendingModel(QSqlDatabase &db, QObject *parent=nullptr);

    int firstColumn() const override;
    int lastColumn() const override;

    QHash<int, QMetaType::Type> dataTypes() const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    static const QHash<int, QByteArray> ROLE_NAMES;
    static const QHash<int, QMetaType::Type> DATA_TYPES;;
};

#endif // PENDINGMODEL_H
