import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../items" as Items

import com.gemini.enums 0.1
import com.gemini.helper 0.1

GDialog {
    id: root

    dialog: Enums.Dialog.NewPlaylistDialog
    headerText: "New playlist"

    standardButtons: Dialog.Cancel | Dialog.Ok
    acceptEnabled: (!Helper.empty(playlist.text) && !dataController.containsData({"name": playlist.text}, Enums.Data.Playlist))

    contentItem: Items.GInput {
        id: playlist

        Layout.fillWidth: true
        focus: true
        placeholderText: qsTr("Playlist name")
    }

    onAccepted: callback(playlist.text)
}
