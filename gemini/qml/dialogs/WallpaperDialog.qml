import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1
import com.gemini.styles 0.1

import "../components/wallpapers" as Wallpapers

GDialog {
    id: root

    property alias source: wallpaper.source

    header: null
    footer: null
    background: null

    dialog: Enums.Dialog.WallpaperDialog
    standardButtons: Dialog.NuButton

    closePolicy: Popup.CloseOnEscape

    contentItem: Wallpapers.WallpaperWithDetails {
        id: wallpaper
    }
}
