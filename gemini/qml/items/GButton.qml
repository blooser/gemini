import QtQuick 2.14
import QtQuick.Controls 2.12

import com.gemini.styles 0.1

Button {
    id: root

    property alias radius: backgroundRectangle.radius
    property alias border: backgroundRectangle.border

    font.capitalization: Font.AllUppercase

    contentItem: GText {
        text: root.text
        font: root.font
        opacity: enabled ? GeminiStyles.opacityVisible : GeminiStyles.opacityDisabledVisible
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        id: backgroundRectangle

        implicitWidth: GeminiStyles.controlImplicitWidth
        implicitHeight: GeminiStyles.controlImplicitHeight

        opacity: enabled ? GeminiStyles.opacityVisible : GeminiStyles.opacityDisabledVisible
        color: checked ? GeminiStyles.highlightColor : GeminiStyles.geminiThirdColor

        border {
            color: GeminiStyles.geminiBaseColor
            width: GeminiStyles.borderWidth
        }
    }
}
