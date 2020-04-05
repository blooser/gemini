import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1
import com.gemini.styles 0.1

import "../../items" as Items

Item {
    id: root

    implicitWidth: playlistSwitcherCurrentItem.implicitWidth
    implicitHeight: playlistSwitcherCurrentItem.implicitHeight

    CurrentPlaylistSwitcherCurrentItem {
        id: playlistSwitcherCurrentItem

        anchors.fill: parent
        displayPlaylist: sessionController.currentPlaylist.name

        onClicked: playlistSwitcherItems.open()
    }

    CurrentPlaylistSwitcherItems {
        id: playlistSwitcherItems

        anchors.fill: parent

        onPlaylistSelected: playlistSwitcherCurrentItem.displayPlaylist = playlistName
    }
}
