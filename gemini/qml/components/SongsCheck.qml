import QtQuick 2.14

import com.gemini.enums 0.1

import "../items" as Items

Item {
    id: root

    property var selectedSongs: []

    implicitWidth: songs.implicitWidth
    implicitHeight: songs.implicitHeight

    ListView {
        id: songs

        anchors.fill: parent

        clip: true

        model: songModel

        delegate: Items.GCheckBox {
            text: name

            enabled: !dataController.containsData({"playlist": sessionController.currentPlaylist.id,
                                                   "song": id}, Enums.Data.Relations)

            onCheckStateChanged: {
                if (checkState === Qt.Checked) {
                    selectedSongs.push(id)
                } else if (checkState === Qt.Unchecked) {
                    selectedSongs.splice(selectedSongs.indexOf(id), 1)
                }

                root.selectedSongsChanged()
            }
        }
    }
}
