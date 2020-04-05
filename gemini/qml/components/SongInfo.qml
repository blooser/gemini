import QtQuick 2.14

import com.gemini.styles 0.1

import "../items" as Items

Items.GText {
    id: root

    horizontalAlignment: Text.AlignLeft
    wrapMode: Text.WordWrap

    font {
        pixelSize: GeminiStyles.bFontPixelSize
        bold: true
    }
}
