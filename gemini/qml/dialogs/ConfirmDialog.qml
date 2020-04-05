import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../items" as Items

import com.gemini.enums 0.1
import com.gemini.styles 0.1

GDialog {
    id: root

    property alias text: textItem.text

    dialog: Enums.Dialog.ConfirmDialog
    headerText: qsTr("Confirm delete")

    standardButtons: Dialog.No | Dialog.Yes

    implicitWidth: 600

    contentItem: Items.GText {
        id: textItem

        wrapMode: Text.WordWrap

        font.pixelSize: GeminiStyles.bFontPixelSize
    }

    onAccepted: callback()
}
