import QtQuick 2.14
import QtQuick.Controls 2.14

import com.gemini.styles 0.1

ScrollBar {
    id: root

    active: true
    orientation: Qt.Vertical

    contentItem: Rectangle {
        radius: width/2
        color: root.pressed ? GeminiStyles.highlightColor
                            : root.active ? GeminiStyles.geminiThirdColor
                                          : GeminiStyles.geminiSecondColor

        state: "vertical"
        states: [
            State {
                name: "vertical"
                when: (root.orientation === Qt.Vertical)
                PropertyChanges { target: contentItem; implicitWidth: 6; implicitHeight: 100 }
            },

            State {
                name: "horizontal"
                when: (root.orientation === Qt.Horizontal)
                PropertyChanges { target: contentItem; implicitWidth: 100; implicitHeight: 6 }
            }
        ]

        Behavior on color {
            ColorAnimation { duration: GeminiStyles.quickAnimation }
        }
    }
}
