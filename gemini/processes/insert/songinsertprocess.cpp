#include "songinsertprocess.h"

#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tpropertymap.h>

#include "../../common/enums.h"

namespace {
    constexpr Enums::Data SONGS = Enums::Data::Songs;
}

SongInsertProcess::SongInsertProcess(const std::shared_ptr<ModelController> &modelController,
                                     const std::shared_ptr<FilesController> &filesController,
                                     const QVariant &data)
    : PendableProcess(data, modelController),
    m_modelController(modelController),
    m_filesController(filesController) {

}

QVariantMap SongInsertProcess::modelData(const QVariant &data) const {
    TagLib::FileRef file(data.toUrl().path().toUtf8());
    auto tag = file.tag();
    auto audio = file.audioProperties();

    if (not audio) {
        return {};
    }

    return {
        { "title", tag->title().toCString() },
        { "artist", tag->artist().toCString() },
        { "date", tag->year() },
        { "album", tag->album().toCString() },
        { "genre", tag->genre().toCString() },
        { "duration", audio->length() },
        { "url", data.toUrl() }
    };
}

void SongInsertProcess::start() {
    auto newUrl = m_filesController->put(inputData().toUrl(), SONGS);
    if (not newUrl.isEmpty()) {
        m_modelController->appendData(modelData(newUrl), SONGS);
        finishPending();
    }
}
