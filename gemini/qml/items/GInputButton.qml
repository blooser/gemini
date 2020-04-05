import QtQuick 2.14

GInput {
    id: root

    readOnly: true

    signal clicked()

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
