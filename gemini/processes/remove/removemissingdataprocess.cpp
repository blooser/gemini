#include "removemissingdataprocess.h"

#include <QFileInfo>

namespace {
    constexpr Enums::Data SONGS = Enums::Data::Songs;
    constexpr Enums::Data WALLPAPERS = Enums::Data::Wallpapers;
    QByteArray URL_ROLENAME = QByteArrayLiteral("url");
}

RemoveMissingDataProcess::RemoveMissingDataProcess(const std::shared_ptr<ModelController> &modelController)
    : Process(QVariant()),
      m_modelController(modelController) {

}

QVariantMap RemoveMissingDataProcess::modelData(const QVariant &data) const {
    return {
        { "url", data.toUrl().path() }
    };
}

void RemoveMissingDataProcess::start() {
    for (const auto &url : collectMissing(SONGS)) {
        m_modelController->removeData(modelData(url), SONGS);
    }

    for (const auto &url : collectMissing(WALLPAPERS)) {
        m_modelController->removeData(modelData(url), WALLPAPERS);
    }
}

 QVector<QUrl> RemoveMissingDataProcess::collectMissing(Enums::Data data) {
    QVector<QUrl> missingData;
    QUrl url;
    for (const auto &data :  m_modelController->readData(URL_ROLENAME, data)) {
        url = data.toUrl();

        if (not QFileInfo(url.path()).exists()) {
            missingData.append(url);
        }
    }

    return missingData;
}
