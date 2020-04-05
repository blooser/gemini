#ifndef PAGEITEM_H
#define PAGEITEM_H

#include <QObject>
#include <QUrl>
#include <QString>

namespace data {

struct PageItem {
    Q_GADGET
    Q_PROPERTY(QUrl icon MEMBER m_icon)
    Q_PROPERTY(QString name MEMBER m_name)

public:
    QUrl m_icon;
    QString m_name;
};

}

Q_DECLARE_METATYPE(data::PageItem)

#endif // PAGEITEM_H
