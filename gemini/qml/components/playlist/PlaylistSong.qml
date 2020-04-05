import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../items" as Items

Rectangle {
    id: root

    property alias text: textItem.text
    property bool playing: false

    signal remove()

    color: GeminiStyles.geminiThirdColor

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        Items.GText {
            id: textItem

            Layout.fillWidth: true

            color: root.playing ? GeminiStyles.highlightColor : GeminiStyles.geminiTextBaseColor
            font.bold: root.playing
            horizontalAlignment: Text.AlignLeft
            padding: GeminiStyles.tMargin
        }

        Items.GImageButton {
            Layout.preferredWidth: 32
            Layout.preferredHeight: 32

            radius: GeminiStyles.none
            border.width: GeminiStyles.none

            iconSource: "qrc:/icons/delete"

            onClicked: root.remove()
        }
    }
}
