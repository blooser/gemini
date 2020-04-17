import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.helper 0.1
import com.gemini.tools 0.1
import com.gemini.enums 0.1
import com.gemini.styles 0.1
import com.gemini.common 0.1

import ".." as Components
import "../../items" as Items
import "../separator" as Separator

Item {
    id: root

    property bool allSongs: false

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        anchors.fill: parent

        spacing: GeminiStyles.tMargin

        PlaylistItem {
            Layout.fillWidth: true
            Layout.rightMargin: GeminiStyles.tMargin

            highlighted: root.allSongs

            text: qsTr("All Songs")
            removable: false
            info.songs: songModel.size

            onClicked: root.allSongs = true
        }

        ListView {
            id: items

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rightMargin: GeminiStyles.tMargin

            clip: true
            model: playlistModel

            spacing: GeminiStyles.tMargin

            delegate: PlaylistItem {
                width: items.width
                text: name

                info.songs: songs
                info.duration: Utility.formatTime(duration * 1000, "mm:ss")

                highlighted: (id === sessionController.currentPlaylist.id && !root.allSongs)

                onClicked: {
                    root.allSongs = false
                    sessionController.selectPlaylist(index, Playlist.SelectByIndex)
                }

                onRemove: objectController.openDialog(Enums.Dialog.ConfirmDialog, {"text": qsTr("Are you sure you want to delete the <b>%1</b> playlist?").arg(name)}, function() {
                    if (id === sessionController.currentPlaylist.id) {
                        sessionController.selectPlaylist(Helper.selectNextIndex(index, items.count), Playlist.SelectByIndex)
                    }

                    dataController.removeData([id], Enums.Data.Playlist)
                })
            }
        }
    }
}
