import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.tools 0.1

import "../../items" as Items

Item {
    id: root

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    property bool playing: false

    readonly property url playbackIcon:{
        switch (sessionController.playback) {
        case Playlist.Sequental:
            return "qrc:/icons/sequental"
        case Playlist.Loop:
            return "qrc:/icons/loop"
        case Playlist.Random:
            return "qrc:/icons/random"

        }
    }

    Connections {
        target: sessionController

        onSwitchAudioMute: audioMuteButton.checked = !audioMuteButton.checked
    }

    GridLayout {
        id: mainLayout

        columns: 5
        rows: 2

        anchors.fill: parent

        Items.GImageButton {
            Layout.column: 0
            Layout.row: 0
            Layout.alignment: Qt.AlignLeft

            iconSource: "qrc:/icons/previous"

            onClicked: sessionController.previousSong()
        }

        Items.GImageButton {
            Layout.column: 1
            Layout.row: 0
            Layout.alignment: Qt.AlignLeft

            iconSource: playbackIcon

            onClicked: sessionController.switchPlayback()
        }

        Items.GImageButton {
            Layout.column: 2
            Layout.row: 0
            Layout.alignment: Qt.AlignHCenter

            iconSource: playing ? "qrc:/icons/pause" : "qrc:/icons/play"

            onClicked: sessionController.togglePlayer()
        }

        Items.GImageButton {
            id: audioMuteButton

            Layout.column: 3
            Layout.row: 0
            Layout.alignment: Qt.AlignRight

            iconSource: "qrc:/icons/mute"
            checkable: true

            onCheckedChanged: sessionController.audioMuted = checked

            Component.onCompleted: {
                checked = sessionController.audioMuted
            }
        }

        Items.GImageButton {
            Layout.column: 4
            Layout.row: 0
            Layout.alignment: Qt.AlignRight

            iconSource: "qrc:/icons/next"

            onClicked: sessionController.nextSong()
        }

        Items.GSlider {
            id: volumeSlider

            Layout.column: 0
            Layout.columnSpan: 5
            Layout.row: 1
            Layout.alignment: Qt.AlignHCenter

            from: 0
            value: 50
            to: 100

            iconVisible: true
            iconSource: "qrc:/icons/volume"

            onValueChanged: sessionController.audioVolume = value

            Items.GToolTip {
                parent: volumeSlider.handle
                visible: volumeSlider.pressed
                text: volumeSlider.value.toFixed(0)
            }

            Component.onCompleted: {
                value = sessionController.audioVolume
            }
        }
    }
}
