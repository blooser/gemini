import QtQuick 2.14
import QtQuick.Controls 2.12

import com.gemini.styles 0.1

Slider {
    id: root

    property bool iconVisible: false
    property alias iconSource: icon.source

    background: Rectangle {
        x: root.leftPadding
        y: root.topPadding + root.availableHeight/2 - height/2

        implicitWidth: 250
        implicitHeight: 4

        width: root.availableWidth
        height: implicitHeight

        radius: GeminiStyles.tMargin
        color: GeminiStyles.geminiThirdColor

        Rectangle {
            width: root.visualPosition * parent.width
            height: parent.height
            color: GeminiStyles.highlightColor
            radius: parent.radius
        }
    }

    handle: Rectangle {
        x: root.leftPadding + root.visualPosition * (root.availableWidth - width)
        y: root.topPadding + root.availableHeight/2 - height/2

        implicitWidth: 26
        implicitHeight: 26
        radius: 13

        color: root.pressed ? GeminiStyles.highlightColor : GeminiStyles.geminiThirdColor
        border.color: GeminiStyles.geminiSecondColor

        Behavior on color {
            ColorAnimation { duration: GeminiStyles.quickAnimation }
        }

        Image {
            id: icon

            anchors {
                fill: parent
                margins: GeminiStyles.tMargin
            }

            fillMode: Image.PreserveAspectFit
        }
    }
}
