import QtQuick 2.14

import com.gemini.styles 0.1

import ".." as Components

Components.Label {
    id: root

    property bool hidden: false

    states: State {
        name: "hidden"
        when: root.hidden

        PropertyChanges {
            target: root
            opacity: GeminiStyles.none
            implicitWidth: GeminiStyles.none
            implicitHeight: GeminiStyles.none
        }
    }

    state: "hidden"

    transitions:  [
        Transition {
            from: "*"; to: "hidden"

            SequentialAnimation {
                OpacityAnimator { duration: GeminiStyles.quickAnimation }
                NumberAnimation { properties: "implicitWidth, implicitHeight"; duration: GeminiStyles.quickAnimation }
            }
        },

        Transition {
            from: "hidden"; to: "*"

            SequentialAnimation {
                NumberAnimation { properties: "implicitWidth, implicitHeight"; duration: GeminiStyles.quickAnimation }
                OpacityAnimator { duration: GeminiStyles.quickAnimation }
            }
        }
    ]
}
