import QtQuick 2.14

import com.gemini.styles 0.1

import ".." as Components

Components.Label {
    id: root

    property bool hiddenOn: false

    states: State {
        name: "hidden"
        when: root.hiddenOn

        PropertyChanges {
            target: root
            opacity: 0
            implicitWidth: 0
            implicitHeight: 0
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
