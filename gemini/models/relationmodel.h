#ifndef RELATIONMODEL_H
#define RELATIONMODEL_H

#include "sqltablemodel.h"

#include <QHash>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(relationModel)

class RelationModel : public SqlTableModel {
    Q_OBJECT

public:
    enum Column {
        Playlist = Qt::UserRole + 1,
        Song,

        Last
    };

    explicit RelationModel(QSqlDatabase &db, QObject *parent=nullptr);

    int firstColumn() const override;
    int lastColumn() const override;

    QHash<int, QMetaType::Type> dataTypes() const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    static const QHash<int, QByteArray> ROLE_NAMES;
    static const QHash<int, QMetaType::Type> DATA_TYPES;;

};

#endif // RELATIONMODEL_H
