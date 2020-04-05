import QtQuick 2.14

import com.gemini.styles 0.1

Text {
    id: root

    color: GeminiStyles.geminiTextBaseColor

    style: Text.Raised
    styleColor: GeminiStyles.geminiTextStyleBaseColor

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter

    font.pixelSize: GeminiStyles.tFontPixelSize

    elide: Text.ElideRight
}
