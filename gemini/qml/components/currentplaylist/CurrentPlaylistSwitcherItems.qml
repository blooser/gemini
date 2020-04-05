import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.helper 0.1
import com.gemini.tools 0.1
import com.gemini.styles 0.1
import com.gemini.enums 0.1

Item {
    id: root

    signal playlistSelected(string playlistName)

    function open() {
        popup.open()
    }

    function close() {
        popup.close()
    }

    implicitWidth: playlists.implicitWidth
    implicitHeight: playlists.implicitHeight

    Popup {
        id: popup

        width: root.width
        implicitHeight: contentItem.implicitHeight

        padding: GeminiStyles.none

        contentItem: ListView {
            id: playlists

            implicitHeight: 400

            model: playlistModel ? playlistModel : []

            delegate: CurrentPlaylistSwitcherItem {
                width: playlists.width

                text: name

                onClicked: {
                    sessionController.selectPlaylist(index, Playlist.SelectByIndex)
                    root.close()
                }

                onRemove: objectController.openDialog(Enums.Dialog.ConfirmDialog, {"text": qsTr("Are you sure you want to delete <b>%1</b> playlist?").arg(name)}, function(){
                    if (id === sessionController.currentPlaylist.id) {
                        sessionController.selectPlaylist(Helper.selectNextIndex(index, playlists.count), Playlist.SelectByIndex)
                    }

                    dataController.removeData([id], Enums.Data.Playlist)
                })
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            radius: GeminiStyles.tMargin
            color: GeminiStyles.geminiBaseColor
        }
    }
}
