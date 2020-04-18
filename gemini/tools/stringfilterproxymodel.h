#ifndef STRINGFILTERPROXYMODEL_H
#define STRINGFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QQmlParserStatus>
#include <QObject>

class StringFilterProxyModel : public QSortFilterProxyModel,
                               public QQmlParserStatus {
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QString string READ string
               WRITE setString NOTIFY stringChanged)
    Q_PROPERTY(QString role READ role
               WRITE setRole NOTIFY roleChanged)

public:
    StringFilterProxyModel(QObject *parent = nullptr);

    // QQmlParserStatus
    void classBegin() override;
    void componentComplete() override;

    QString string() const;
    void setString(const QString &string);

    QString role() const;
    void setRole(const QString &role);

signals:
    void stringChanged(const QString &string);
    void roleChanged(const QString &role);

private:
    QString m_string;
    QString m_role;

    void setRoleIfNeeded();
};

#endif // STRINGFILTERPROXYMODEL_H
