#include "objectcontroller.h"

#include "../common/utility.h"
#include "../paths/paths.h"

Q_LOGGING_CATEGORY(objectController, "object.controller")

namespace {
    const QString DIALOG_PREFIX = QStringLiteral("qrc:/dialogs");
    const QString QML_SUFFIX = QStringLiteral(".qml");
}

ObjectController::ObjectController(QObject *parent)
    : QObject(parent) {

}

void ObjectController::openDialog(Enums::Dialog popup, const QVariantMap &properties, const QVariant &callback) {
    QString popupUrl = path(popup);
    qCInfo(objectController) << "New object" << popupUrl;
    emit open(popupUrl, properties, callback);
}

QString ObjectController::path(Enums::Dialog popup) {
    return paths::join(DIALOG_PREFIX, Utility::enumToString(popup) + QML_SUFFIX);
}
