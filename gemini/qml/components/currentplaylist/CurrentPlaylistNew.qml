import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.helper 0.1
import com.gemini.styles 0.1
import com.gemini.enums 0.1

import "../../items/headers" as Headers

Rectangle {
    id: root

    color: GeminiStyles.geminiSecondColor

    implicitWidth: GeminiStyles.playlistNewImplicitWidth
    implicitHeight: GeminiStyles.playlistNewImplicitWidth

    Headers.ButtonHeader {
        anchors.centerIn: root

        header: qsTr("There is no playlist")
        contentText: qsTr("Create new playlist")

        onClicked: objectController.openDialog(Enums.Dialog.NewPlaylistDialog, {}, function(playlist) {
            if (!Helper.empty(playlist)) {
                dataController.insertData([playlist], Enums.Data.Playlist)
            }
        });
    }
}

