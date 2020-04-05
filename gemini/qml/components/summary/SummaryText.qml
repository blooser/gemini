import QtQuick 2.14

import com.gemini.styles 0.1

import "../../items" as Items

Rectangle {
    id: root

    property alias text: text.text

    implicitWidth: text.implicitWidth
    implicitHeight: text.implicitHeight

    Items.GText {
        id: text
        anchors.fill: parent
        padding: GeminiStyles.tMargin
        font.pixelSize: GeminiStyles.summaryNumberFontPixelSize
    }
}
