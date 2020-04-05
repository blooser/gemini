#include "utility.h"

#include <QDateTime>
#include <QFileInfo>
#include <QLocale>
#include <QUrl>

Utility &Utility::instance() {
    static Utility utility;
    return utility;
}

bool Utility::isPendable(Enums::Data data) {
    return (data == Enums::Data::Songs || data == Enums::Data::Wallpapers);
}

QString Utility::formatTime(const int ms, const QString &format) {
    return ((ms < 0) ? QDateTime::fromMSecsSinceEpoch(0)
                     : QDateTime::fromMSecsSinceEpoch(ms)).toString(format);
}

QString Utility::fileSize(const QUrl &url) {
    QLocale locale;
    return locale.formattedDataSize(QFileInfo(url.path()).size());
}

Utility::Utility(QObject *parent)
    : QObject(parent) {

}
