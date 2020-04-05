import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1
import com.gemini.styles 0.1
import com.gemini.helper 0.1

import "../../items" as Items

Item {
    id: root

    property alias displayPlaylist: playlistButton.text

    signal clicked()

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        spacing: GeminiStyles.tMargin

        Items.GImageButton {
            Layout.preferredWidth: 32
            Layout.preferredHeight: 32

            iconSource: "qrc:/icons/music"
            enabled: (songModel.size !== GeminiStyles.empty)

            onClicked: objectController.openDialog(Enums.Dialog.SongsDialog, {"headerText": qsTr("Add songs to <b>%1</b>".arg(displayPlaylist))}, function(songs){
                if (!Helper.empty(songs)) {
                    dataController.insertData(Helper.createRelation(sessionController.currentPlaylist.id, songs), Enums.Data.Relations)
                }
            })
        }

        Items.GInputButton {
            id: playlistButton

            Layout.fillWidth: true

            onClicked: root.clicked()
        }
    }
}
