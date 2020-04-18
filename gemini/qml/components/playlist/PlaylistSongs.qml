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

    implicitWidth: songs.implicitWidth
    implicitHeight: songs.implicitHeight

    onAllSongsChanged: selectedSongs = []

    Connections {
        target: sessionController

        onCurrentPlaylistChanged: selectedSongs = []
        onClearSelection: selectedSongs = []
    }

    ListView {
        id: songs

        anchors.fill: parent

        clip: true
        spacing: GeminiStyles.tMargin
        model: root.allSongs ? songModel : songsInRelations

        delegate: PlaylistSong {
            width: songs.width
            playing: (!root.allSongs && id === sessionController.currentSong.id && sessionController.currentSong.playlist.id === sessionController.currentPlaylist.id)

            songTitle: title
            songDuration: Utility.formatTime(duration * 1000, "mm:ss")

            property int indexInSelectedSongs: selectedSongs.findIndex(song => (allSongs) ? song.id === id : song.song === id)
            property bool selected: (indexInSelectedSongs !== -1)

            border.color: selected ? GeminiStyles.highlightColor : GeminiStyles.blank

            onClicked: {
                if (!selected) {
                    selectedSongs.push(allSongs ? {"id": id} : {"playlist": sessionController.currentPlaylist.id, "song": id})
                } else {
                    selectedSongs.splice(indexInSelectedSongs, 1)
                }

                root.selectedSongsChanged()
            }

            onRemove: {
                const message = allSongs ? qsTr("Are you sure you want to delete <b>%1</b> song?").arg(title)
                                         : qsTr("Are you sure you want to delete <b>%1</b> song from <b>%2</b> playlist?").arg(title).arg(sessionController.currentPlaylist.name)

                objectController.openDialog(Enums.Dialog.ConfirmDialog, {"text": message}, function() {
                    if (allSongs) {
                        dataController.removeData([{"id": id, "url": url}], Enums.Data.Songs)
                    } else {
                        dataController.removeData([{"playlist": sessionController.currentPlaylist.id, "song": id}], Enums.Data.Relations)
                    }
                })
            }

            Component.onDestruction: {
                selectedSongs.splice(indexInSelectedSongs, 1)
                root.selectedSongsChanged()
            }
        }
    }
}
