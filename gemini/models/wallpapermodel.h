#ifndef WALLPAPERMODEL_H
#define WALLPAPERMODEL_H

#include "sqltablemodel.h"

#include <QObject>
#include <QHash>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(wallpaperModel)

class WallpaperModel : public SqlTableModel {
    Q_OBJECT

public:
    enum Column {
        Id = Qt::UserRole + 1,
        Name,
        Url,

        Last
    };

    explicit WallpaperModel(QSqlDatabase &db, QObject *parent = nullptr);


    int firstColumn() const override;
    int lastColumn() const override;

    QHash<int, QMetaType::Type> dataTypes() const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    static const QHash<int, QByteArray> ROLE_NAMES;
    static const QHash<int, QMetaType::Type> DATA_TYPES;
};

#endif // WALLPAPERMODEL_H
