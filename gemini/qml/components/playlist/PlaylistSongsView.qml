import QtQuick 2.14
import QtQuick.Controls 2.14

import com.gemini.common 0.1
import com.gemini.enums 0.1
import com.gemini.styles 0.1

import ".." as Components
import "../dynamic" as Dynamic

Item {
    id: root

    property bool allSongs: false

    property var selectedSongs: []

    implicitWidth: changer.implicitWidth
    implicitHeight: changer.implicitHeight

    Binding on selectedSongs {
        value: changer.currentItem.selectedSongs
        when: !changer.when // NOTE: When the main item is PlaylistSongs
    }

    Dynamic.Changer {
        id: changer

        anchors {
            fill: parent
            leftMargin: GeminiStyles.tMargin
        }

        main: PlaylistSongs {
            allSongs: root.allSongs
        }

        replace:  Components.TileText {
            text: qsTr("Try to add a new songs")
        }

        when: (songModel.size === GeminiStyles.empty)
    }
}
