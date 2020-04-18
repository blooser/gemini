#include "stringfilterproxymodel.h"

StringFilterProxyModel::StringFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {
    setDynamicSortFilter(true);
    setFilterCaseSensitivity(Qt::CaseInsensitive);

}

void StringFilterProxyModel::classBegin() {

}

void StringFilterProxyModel::componentComplete() {
    setRoleIfNeeded();
}

QString StringFilterProxyModel::string() const {
    return m_string;
}

void StringFilterProxyModel::setString(const QString &string) {
    if (m_string == string) {
        return;
    }

    m_string = string;
    emit stringChanged(m_string);

    setRoleIfNeeded();
    setFilterWildcard("*" + m_string + "*");
}

QString StringFilterProxyModel::role() const {
    return m_role;
}

void StringFilterProxyModel::setRole(const QString &role) {
    if (m_role == role) {
        return;
    }

    m_role = role;
    emit roleChanged(m_role);
}

void StringFilterProxyModel::setRoleIfNeeded() {
    if (sourceModel()) {
        auto roleNumber = sourceModel()->roleNames().key(m_role.toUtf8());

        if (filterRole() != roleNumber) {
            setFilterRole(roleNumber);
        }
    }
}
