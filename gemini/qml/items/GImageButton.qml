import QtQuick 2.14

GButton {
    id: root

    property alias iconSource: image.source

    implicitWidth: 34
    implicitHeight: 34

    radius: 5
    padding: 5

    contentItem: Image {
        id: image
        smooth: true
        fillMode: Image.PreserveAspectFit
    }
}
