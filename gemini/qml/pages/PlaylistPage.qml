import QtQuick 2.14

import Qt.labs.platform 1.1

import com.gemini.helper 0.1
import com.gemini.enums 0.1
import com.gemini.styles 0.1

import "../components/pageheaders" as PageHeaders
import "../components/playlist" as Playlist

GPage {
    id: root

    header: PageHeaders.PlaylistPageHeader {
        selectedSongs: playlistView.selectedSongs

        onNewPlaylist: objectController.openDialog(Enums.Dialog.NewPlaylistDialog, {}, function(playlistName){
            dataController.insertData([playlistName], Enums.Data.Playlist)
        })

        onAddSongs: {
            if (playlistView.allSongs || songModel.size === GeminiStyles.empty) {
                objectController.openDialog(Enums.Dialog.FileOpenDialog, {"title": qsTr("Add new songs"),
                                                                          "nameFilters": ["Music (*.mp3 *.wav *.flac *.m4a)"],
                                                                          "folder": StandardPaths.writableLocation(StandardPaths.MusicLocation)}, function(files) {
                    dataController.insertData(Helper.toList(files), Enums.Data.Songs)
                })
            } else {
                objectController.openDialog(Enums.Dialog.SongsDialog, {"headerText": qsTr("Add songs to <b>%1</b> playlist").arg(sessionController.currentPlaylist.name) }, function(songs) {
                    dataController.insertData(Helper.createRelation(sessionController.currentPlaylist.id, songs), Enums.Data.Relations)
                })
            }
        }

        onRemoveSelectedSongs: {
            objectController.openDialog(Enums.Dialog.ConfirmDialog, {"text": qsTr("Are you sure you want to delete <b>%1</b> songs?").arg(selectedSongs.length)}, function() {
                dataController.removeData(selectedSongs, playlistView.allSongs ? Enums.Data.Songs : Enums.Data.Relations)
                sessionController.clearSelection() // NOTE: This will take effects in PlaylistSongs
            })
        }
    }

    Playlist.PlaylistView {
        id: playlistView

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }
    }
}
