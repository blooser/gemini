import QtQuick 2.14
import QtGraphicalEffects 1.0

import "../../items" as Items

import com.gemini.styles 0.1

Item {
    id: root

    Desaturate {
        cached: false
        source: root.parent
        desaturation: 1.0
        anchors.fill: root
    }

    Items.GText {
        anchors.centerIn: root
        text: qsTr("Selected")
    }
}
