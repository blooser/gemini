import QtQuick 2.14
import QtQuick.Controls 2.14

import Qt.labs.settings 1.1

import com.gemini.styles 0.1

import "../../items" as Items

Item {
    id: root

    property alias allSongs: playlistItems.allSongs
    property alias selectedSongs: playlistSongsView.selectedSongs

    Items.GSplitView {
        id: splitView

        orientation: Qt.Horizontal

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        PlaylistItems {
            id: playlistItems

            SplitView.preferredWidth: 250
        }

        PlaylistSongsView {
            id: playlistSongsView

            allSongs: root.allSongs

            SplitView.fillWidth: true
        }
    }

    Settings {
        id: settings
        property var splitView
    }

    Component.onCompleted: {
        if (playlistModel.size === GeminiStyles.empty) {
            root.allSongs = true
        }

        splitView.restoreState(settings.splitView)
    }

    Component.onDestruction: settings.splitView = splitView.saveState()
}
