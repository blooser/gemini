import QtQuick 2.14

import com.gemini.styles 0.1

import "../../items" as Items

Rectangle {
    id: root

    property alias number: number.text

    implicitWidth: number.implicitWidth
    implicitHeight: number.implicitHeight

    Items.GText {
        id: number
        anchors.fill: parent
        padding: GeminiStyles.tMargin
        font.pixelSize: GeminiStyles.summaryNumberFontPixelSize
    }
}
