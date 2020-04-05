import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.tools 0.1
import com.gemini.styles 0.1

Item {
    id: root

    implicitWidth: songs.implicitWidth
    implicitHeight: songs.implicitHeight

    ListView {
        id: songs

        anchors.fill: parent

        model: songsInRelations

        delegate: CurrentPlaylistSong {
            width: songs.width

            text: name

            current: (sessionController.currentSong.id === id && sessionController.currentSong.playlist.id === sessionController.currentPlaylist.id)

            onSongSelected: sessionController.selectSong(index, Playlist.SelectByIndex)
        }
    }
}
