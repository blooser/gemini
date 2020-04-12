import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../items" as Items

Items.GToolBar {
    id: root

    signal addWallpapers()
    signal removeSelectedWallpapers()

    property var selectedWallpapers: []

    implicitWidth: mainLayout.implicitWidth

    // TODO: Make a special component for these button alignment
    RowLayout {
        id: mainLayout

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Items.GToolButton {
                text: qsTr("Add wallpapers")

                onClicked: root.addWallpapers()
            }

            Items.GToolButton {
                id: removeSelectedWallpapersToolButton

                text: qsTr("Remove %1 wallpapers").arg(selectedWallpapers.length)

                onClicked: root.removeSelectedWallpapers()
            }
        }
    }

    states: [
        State {
            when: !selectedWallpapers.length
            PropertyChanges { target: removeSelectedWallpapersToolButton; implicitWidth: GeminiStyles.none; implicitHeight: GeminiStyles.none; opacity: GeminiStyles.hidden }
        }
    ]

    transitions: Transition {
        ParallelAnimation {
            NumberAnimation { property: "opacity"; duration: GeminiStyles.quickAnimation }
            NumberAnimation { properties: "implicitWidth, implicitHeight"; duration: GeminiStyles.quickAnimation }
        }
    }
}
