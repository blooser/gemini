import QtQuick 2.14

import com.gemini.styles 0.1
import com.gemini.enums 0.1

import "../../items" as Items

Items.GImageButton {
    id: root

    implicitWidth: GeminiStyles.wallpaperCloseButtonWidth
    implicitHeight: GeminiStyles.wallpaperCloseButtonHeight

    iconSource: "qrc:/icons/close"
    radius: (width/2)

    onClicked: objectController.close(Enums.Dialog.WallpaperDialog)
}
