#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>

namespace Enums {
    Q_NAMESPACE

    enum class Data {
        Unknown = -1,

        Wallpapers,
        Playlist,
        Songs,
        Relations,
        Pending,
    };
    Q_ENUM_NS(Data)
    inline uint qHash(Data key, uint seed) { return ::qHash(static_cast<int>(key), seed); }

    enum class Dialog {
        Unknown = -1,

        NewPlaylistDialog,
        ConfirmDialog,
        FileOpenDialog,
        PendingDialog,
        UnfinishedPendingDialog,
        WallpaperDialog,
        SongsDialog,
        SwitchDialog,
    };
    Q_ENUM_NS(Dialog)
    inline uint qHash(Dialog key, uint seed) { return ::qHash(static_cast<int>(key), seed); }
}

#endif // ENUMS_H
