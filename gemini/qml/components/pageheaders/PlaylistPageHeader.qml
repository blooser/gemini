import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../items" as Items

Items.GToolBar {
    id: root

    signal newPlaylist()
    signal addSongs()
    signal removeSelectedSongs()

    property var selectedSongs: []

    middleContent: RowLayout {
        Items.GToolButton {
            text: qsTr("New playlist")

            onClicked: root.newPlaylist()
        }

        Items.GToolButton {
            text: qsTr("Add songs")

            onClicked: root.addSongs()
        }

        Items.GToolButton {
            id: removeSelectedSongsToolButton

            text: qsTr("Remove %1 songs").arg(selectedSongs.length)

            onClicked: root.removeSelectedSongs()

            state: "hidden"
            states: State {
                name: "hidden"
                when: !selectedSongs.length
                PropertyChanges { target: removeSelectedSongsToolButton; opacity: 0; implicitWidth: 0; implicitHeight: 0; }
            }

            transitions: [
                Transition {
                    from: "*"; to: "hidden"
                    SequentialAnimation {
                        OpacityAnimator { duration: GeminiStyles.quickAnimation }
                        NumberAnimation { properties: "implicitWidth, implicitHeight"; duration: GeminiStyles.quickAnimation }
                    }
                },

                Transition {
                    from: "hidden"; to: "*"
                    SequentialAnimation {
                        NumberAnimation { properties: "implicitWidth, implicitHeight"; duration: GeminiStyles.quickAnimation }
                        OpacityAnimator { duration: GeminiStyles.quickAnimation }
                    }
                }
            ]
        }
    }
}
