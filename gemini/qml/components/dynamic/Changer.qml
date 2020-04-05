import QtQuick 2.0

Item {
    id: root

    property Component main
    property Component replace
    property bool when: false

    states: [
        State {
            when: !root.when
            PropertyChanges { target: loader; sourceComponent: root.main }
        },

        State {
            when: root.when
            PropertyChanges { target: loader; sourceComponent: root.replace }
        }
    ]

    Loader {
        id: loader
        anchors.fill: parent
    }
}
