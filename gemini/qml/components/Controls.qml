import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.helper 0.1
import com.gemini.styles 0.1
import com.gemini.enums 0.1

import "../items" as Items

Item {
    id: root

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        anchors.fill: parent

        spacing: GeminiStyles.tMargin

        Items.GImageButton {
            Layout.preferredWidth: 32
            Layout.preferredHeight: 32

            iconSource: "qrc:/icons/change"

            onClicked: objectController.openDialog(Enums.Dialog.SwitchDialog, {}, null)
        }

        Items.GImageButton {
            Layout.preferredWidth: 32
            Layout.preferredHeight: 32

            iconSource: "qrc:/icons/plus"

            onClicked: objectController.openDialog(Enums.Dialog.NewPlaylistDialog, {}, function(playlist){
                if (!Helper.empty(playlist)) {
                    dataController.insertData([playlist], Enums.Data.Playlist)
                }
            })
        }
    }
}
