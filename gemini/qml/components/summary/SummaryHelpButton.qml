import QtQuick 2.14
import QtGraphicalEffects 1.0

import com.gemini.styles 0.1
import com.gemini.enums 0.1

import "../../items" as Items

Items.GImageButton {
    id: root

    iconSource: "qrc:/icons/gate"
    onClicked: objectController.openDialog(Enums.Dialog.HelpDialog, {}, null)

    RectangularGlow {
        anchors.fill: root
        z: root.contentItem.z - 1
        glowRadius: GeminiStyles.tMargin
        spread: GeminiStyles.none
        cornerRadius: root.radius + glowRadius
        color: GeminiStyles.highlightColor
    }
}
