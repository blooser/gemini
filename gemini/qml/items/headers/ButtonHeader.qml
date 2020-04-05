import QtQuick 2.14
import QtQuick.Layouts 1.12

import ".." as Items

GHeader {
    id: root

    property alias contentText: button.text

    signal clicked()

    Items.GButton {
        id: button
        Layout.fillWidth: true
        onClicked: root.clicked()
    }
}
