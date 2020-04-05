import QtQuick 2.14
import QtQuick.Controls 2.14

import com.gemini.styles 0.1

import "../../items" as Items

Item {
    id: root

    property alias allSongs: playlistItems.allSongs

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

        PlaylistSongs {            
            allSongs: root.allSongs

            SplitView.fillWidth: true
        }
    }

    Component.onCompleted: {
        if (playlistModel.size === GeminiStyles.empty) {
            root.allSongs = true
        }
    }
}
