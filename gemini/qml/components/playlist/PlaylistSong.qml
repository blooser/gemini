import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../items" as Items
import ".." as Components

Rectangle {
    id: root

    property alias songTitle: title.text
    property alias songDuration: duration.text

    property bool playing: false

    signal remove()
    signal clicked()

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    color: GeminiStyles.geminiThirdColor

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        Items.GText {
            id: title

            Layout.fillWidth: true

            color: root.playing ? GeminiStyles.highlightColor : GeminiStyles.geminiTextBaseColor
            font.bold: root.playing
            horizontalAlignment: Text.AlignLeft
            padding: GeminiStyles.tMargin
        }

        Components.TileText {
            id: duration

            Layout.alignment: Qt.AlignCenter

            font.pixelSize: GeminiStyles.tFontPixelSize
            font.family: GeminiStyles.numberFontFamily

            color: GeminiStyles.geminiSecondColor
        }

        Items.GImageButton {
            Layout.preferredWidth: 32
            Layout.preferredHeight: 32

            radius: GeminiStyles.none
            border.width: GeminiStyles.none
            backgroundColor: GeminiStyles.blank

            iconSource: "qrc:/icons/delete"

            onClicked: root.remove()
        }
    }
}
