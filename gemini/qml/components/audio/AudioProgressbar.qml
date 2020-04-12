import QtQuick 2.14

import com.gemini.styles 0.1
import com.gemini.tools 0.1
import com.gemini.common 0.1

import "../../items" as Items

CircleProgressBar {
    id: root

    implicitWidth: GeminiStyles.audioProgressBarImplicitWidth
    implicitHeight: GeminiStyles.audioProgressBarImplicitHeight

    Items.GText {
        anchors.centerIn: parent

        text: Utility.formatTime(value, "mm:ss")
        color: GeminiStyles.highlightColor

        font {
            pixelSize: 24
            bold: true
            family: GeminiStyles.audioProgressBarNumberFontFamily
        }
    }

    Items.GToolTip {
        x: root.mouse.x
        y: root.mouse.y - (height + GeminiStyles.tMargin)

        delay: GeminiStyles.quickAnimation

        visible: root.containsMouse
        text: Utility.formatTime(root.visualValue, "mm:ss")
    }

    Behavior on value {
        NumberAnimation { duration: GeminiStyles.quickAnimation }
    }
}
