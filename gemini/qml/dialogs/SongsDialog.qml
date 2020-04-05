import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1
import com.gemini.helper 0.1

import "../components" as Components

GDialog {
    id: root

    implicitWidth: 850
    implicitHeight: 500

    dialog: Enums.Dialog.SongsDialog
    standardButtons: Dialog.Cancel | Dialog.Ok
    acceptEnabled: !Helper.empty(songsCheck.selectedSongs)

    contentItem: Components.SongsCheck {
        id: songsCheck
    }

    onAccepted: callback(songsCheck.selectedSongs)
}
