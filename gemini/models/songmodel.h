#ifndef SONGMODEL_H
#define SONGMODEL_H

#include "sqltablemodel.h"

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(songModel)

class SongModel : public SqlTableModel {
    Q_OBJECT

public:
    enum Column {
        Id = Qt::UserRole + 1,
        Name,
        Url,

        Last
    };

    explicit SongModel(QSqlDatabase &db, QObject *parent=nullptr);

    int firstColumn() const override;
    int lastColumn() const override;

    QHash<int, QMetaType::Type> dataTypes() const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    static const QHash<int, QByteArray> ROLE_NAMES;
    static const QHash<int, QMetaType::Type> DATA_TYPES;
};

#endif // SONGMODEL_H
