import QtQuick 2.14
import QtQuick.Layouts 1.12

import ".." as Items

GHeader {
    id: root

    property alias text: textItem.text
    property alias horizontalAlignment: textItem.horizontalAlignment

    Items.GText {
        id: textItem
        Layout.fillWidth: true
        wrapMode: Text.WordWrap
    }
}
