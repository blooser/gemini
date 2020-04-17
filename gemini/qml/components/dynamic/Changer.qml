import QtQuick 2.0

Item {
    id: root

    property alias currentItem: loader.item

    property Component main
    property Component replace
    property bool when: false

    state: "main"
    states: [
        State {
            name: "main"
            when: !root.when
            PropertyChanges { target: loader; sourceComponent: root.main }
        },

        State {
            name: "replace"
            when: root.when
            PropertyChanges { target: loader; sourceComponent: root.replace }
        }
    ]

    Loader {
        id: loader
        anchors.fill: parent
    }
}
