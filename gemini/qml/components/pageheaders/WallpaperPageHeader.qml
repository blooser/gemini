import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../items" as Items

Items.GToolBar {
    id: root

    signal addWallpapers()
    signal removeSelectedWallpapers()

    property var selectedWallpapers: []

    middleContent: RowLayout {
        Items.GToolButton {
            text: qsTr("Add wallpapers")

            onClicked: root.addWallpapers()
        }

        Items.GToolButton {
            id: removeSelectedWallpapersToolButton

            text: qsTr("Remove %1 wallpapers").arg(selectedWallpapers.length)

            onClicked: root.removeSelectedWallpapers()

            state: "hidden"

            states: [
                State {
                    name: "hidden"
                    when: !selectedWallpapers.length
                    PropertyChanges { target: removeSelectedWallpapersToolButton; implicitWidth: GeminiStyles.none; implicitHeight: GeminiStyles.none; opacity: GeminiStyles.hidden }
                }
            ]

            transitions: [
                Transition {
                    from: "hidden"; to: "*"
                    SequentialAnimation {
                        NumberAnimation { properties: "implicitWidth, implicitHeight"; duration: GeminiStyles.quickAnimation }
                        NumberAnimation { property: "opacity"; duration: GeminiStyles.quickAnimation }
                    }
                },

                Transition {
                    from: "*"; to: "hidden"
                    SequentialAnimation {
                        NumberAnimation { property: "opacity"; duration: GeminiStyles.quickAnimation }
                        NumberAnimation { properties: "implicitWidth, implicitHeight"; duration: GeminiStyles.quickAnimation }
                    }
                }
            ]
        }
    }
}
