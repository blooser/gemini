import QtQuick 2.14

import Qt.labs.qmlmodels 1.0

TableModel {

    TableModelColumn {
        display: "shortcut"
    }

    TableModelColumn {
        display: "description"
    }

    rows: [
        {
            "shortcut": "CTRL+RIGHT",
            "description": qsTr("Switch to right page")
        },

        {
            "shortcut": "CTRL+LEFT",
            "description": qsTr("Switch to left page")
        },

        {
            "shortcut": "CTRL+S",
            "description": qsTr("Open page dialog")
        },

        {
            "shortcut": "S",
            "description": qsTr("Toggle player")
        },

        {
            "shortcut": "M",
            "description": qsTr("Mute/Unmute")
        },
    ]
}
