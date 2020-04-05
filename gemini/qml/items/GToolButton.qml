import QtQuick 2.14
import QtQuick.Controls 2.14

import com.gemini.styles 0.1

ToolButton {
    id: root

    font.pixelSize: GeminiStyles.tFontPixelSize

    contentItem: GText {
        text: root.text
        font: root.font
        opacity: root.enabled ? GeminiStyles.opacityVisible : GeminiStyles.opacityDisabledVisible
    }

    background: Rectangle {
        implicitWidth: 40
        implicitHeight: 40
        color: GeminiStyles.geminiSecondColor
        opacity: root.enabled ? GeminiStyles.opacityVisible : GeminiStyles.opacityDisabledVisible
    }
}
