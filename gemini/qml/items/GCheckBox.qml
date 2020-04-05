import QtQuick 2.14
import QtQuick.Controls 2.12

import com.gemini.styles 0.1

CheckBox {
    id: root

    opacity: root.enabled ? GeminiStyles.opacityVisible : GeminiStyles.opacityDisabledVisible

    indicator: Rectangle {
        implicitWidth: 26
        implicitHeight: 26

        x: root.leftPadding
        y: root.height/2 - height/2

        radius: GeminiStyles.tMargin

        border {
            color: root.checked ? GeminiStyles.highlightColor : GeminiStyles.geminiBaseColor
            width: root.checked ? GeminiStyles.borderBoldWidth : GeminiStyles.borderWidth
        }

        Image {
            visible: root.checked
            fillMode: Image.PreserveAspectFit

            anchors {
                fill: parent
                margins: GeminiStyles.tMargin
            }

            source: "qrc:/icons/check"
        }
    }

    contentItem: GText {
        text: root.text
        font: root.font
        color: root.checked ? GeminiStyles.highlightColor : GeminiStyles.geminiTextBaseColor
        horizontalAlignment: Text.AlignLeft
        leftPadding: root.indicator.width + root.spacing
    }
}
