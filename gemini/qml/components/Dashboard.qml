import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "currentplaylist" as CurrentPlaylist
import "audio" as Audio

Item {
    id: root

    property bool audioControlEnabled: false

    property alias playing: audioControl.playing
    property alias song: songInfo.song

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    GridLayout {
        id: mainLayout

        anchors.fill: parent

        clip: true

        columns: 2

        SongInfo {
            id: songInfo

            Layout.column: 0
            Layout.row: 0
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop

            visible: !sessionController.cleanScreen
        }

        CurrentPlaylist.CurrentPlaylistView {
            Layout.column: 1
            Layout.row: 0
            Layout.alignment: Qt.AlignRight
            Layout.fillHeight: true
            Layout.preferredWidth: 400
        }

        Audio.AudioControl {
            id: audioControl

            enabled: root.audioControlEnabled

            Layout.column: 0
            Layout.columnSpan: 2
            Layout.row: 2
            Layout.alignment: Qt.AlignCenter

            visible: !sessionController.cleanScreen
        }

        Controls {
            Layout.column: 0
            Layout.row: 1
            Layout.alignment: Qt.AlignLeft

            visible: !sessionController.cleanScreen
        }
    }
}
