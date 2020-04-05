import QtQuick 2.14

import com.gemini.styles 0.1

import "../items" as Items

Rectangle {
    id: root

    property alias text: textItem.text

    implicitWidth: textItem.implicitWidth
    implicitHeight: textItem.implicitHeight

    color: GeminiStyles.geminiSecondColor
    clip: true

    Items.GText {
        id: textItem

        anchors.centerIn: parent
        font.pixelSize: GeminiStyles.hFontPixelSize
        padding: GeminiStyles.tMargin
    }
}
