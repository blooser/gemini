import QtQuick 2.14
import QtQuick.Controls 2.12

import com.gemini.styles 0.1

Button {
    id: root

    property alias radius: backgroundRectangle.radius
    property alias border: backgroundRectangle.border
    property alias backgroundColor: backgroundRectangle.color

    font.capitalization: Font.AllUppercase

    opacity: enabled ? GeminiStyles.opacityVisible : GeminiStyles.opacityDisabledVisible

    contentItem: GText {
        text: root.text
        font: root.font
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        id: backgroundRectangle

        implicitWidth: GeminiStyles.controlImplicitWidth
        implicitHeight: GeminiStyles.controlImplicitHeight

        color: checked ? GeminiStyles.highlightColor : GeminiStyles.geminiThirdColor

        border {
            color: GeminiStyles.geminiBaseColor
            width: GeminiStyles.borderWidth
        }
    }

    Behavior on opacity {
        OpacityAnimator {
            duration: GeminiStyles.quickAnimation
        }
    }
}
