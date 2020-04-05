import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../items" as Items

Items.GToolBar {
    id: root

    signal newPlaylist()
    signal addSongs()

    implicitWidth: mainLayout.implicitWidth

    RowLayout {
        id: mainLayout

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        Items.GToolButton {
            Layout.preferredWidth: 100
            Layout.alignment: Qt.AlignRight

            text: qsTr("New playlist")

            onClicked: root.newPlaylist()
        }

        Items.GToolButton {
            Layout.preferredWidth: 100
            Layout.alignment: Qt.AlignLeft

            text: qsTr("Add songs")

            onClicked: root.addSongs()
        }
    }
}
