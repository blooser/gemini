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
                when: !selectedSongs.length || dataController.processing
                PropertyChanges { target: removeSelectedSongsToolButton; opacity: GeminiStyles.none; implicitWidth: GeminiStyles.none; implicitHeight: GeminiStyles.none; }
            }

            transitions: [
                Transition {
                    from: "*"; to: "hidden"
                    SequentialAnimation {
                        OpacityAnimator { target: removeSelectedSongsToolButton; from: GeminiStyles.visible; to: GeminiStyles.hidden; duration: GeminiStyles.quickAnimation }
                        NumberAnimation { properties: "implicitWidth, implicitHeight"; duration: GeminiStyles.quickAnimation }
                    }
                },

                Transition {
                    from: "hidden"; to: "*"
                    SequentialAnimation {
                        NumberAnimation { properties: "implicitWidth, implicitHeight"; duration: GeminiStyles.quickAnimation }
                        OpacityAnimator { target: removeSelectedSongsToolButton; from: GeminiStyles.hidden; to: GeminiStyles.visible; duration: GeminiStyles.quickAnimation }
                    }
                }
            ]
        }
    }
}
