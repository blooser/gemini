import QtQuick 2.14
import QtQuick.Controls 2.14

import com.gemini.enums 0.1
import com.gemini.styles 0.1

import ".." as Components
import "../dynamic" as Dynamic

Item {
    id: root

    property bool allSongs: false

    implicitWidth: changer.implicitWidth
    implicitHeight: changer.implicitHeight

    Dynamic.Changer {
        id: changer

        anchors {
            fill: parent
            leftMargin: GeminiStyles.tMargin
        }

        main: ListView {
            id: songs

            clip: true
            spacing: GeminiStyles.tMargin
            model: root.allSongs ? songModel : songsInRelations

            delegate: PlaylistSong {
                width: songs.width
                playing: (!root.allSongs && id === sessionController.currentSong.id && sessionController.currentSong.playlist.id === sessionController.currentPlaylist.id)

                text: name

                onRemove: {
                    const message = allSongs ? qsTr("Are you sure you want to delete <b>%1</b> song?").arg(name)
                                             : qsTr("Are you sure you want to delete <b>%1</b> song from <b>%2</b> playlist?").arg(name).arg(sessionController.currentPlaylist.name)

                    objectController.openDialog(Enums.Dialog.ConfirmDialog, {"text": message}, function(){
                        if (allSongs) {
                            dataController.removeData([{"id": id, "url": url}], Enums.Data.Songs)
                        } else {
                            dataController.removeData([{"playlist": sessionController.currentPlaylist.id, "song": id}], Enums.Data.Relations)
                        }
                    })
                }
            }
        }

        replace:  Components.TileText {
            text: qsTr("Try to add a new songs")
        }

        when: (songModel.size === GeminiStyles.empty)
    }
}
