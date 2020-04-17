import QtQuick 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import com.gemini.styles 0.1

import "../../items" as Items
import ".." as Components

ItemDelegate {
    id: root

    property bool removable: true

    property alias info: playlistInfo

    signal remove()

    implicitWidth: 200
    implicitHeight: 64

    contentItem: RowLayout {
        spacing: GeminiStyles.tMargin

        Items.GText {
            Layout.fillWidth: true
            rightPadding: root.spacing
            text: root.text
            font: root.font
            horizontalAlignment: Text.AlignLeft
        }

        PlaylistInfo {
            id: playlistInfo
        }

        Items.GImageButton {
            visible: root.removable
            enabled: root.removable

            Layout.preferredWidth: 32
            Layout.preferredHeight: 32
            Layout.alignment: Qt.AlignRight

            iconSource: "qrc:/icons/delete"

            onClicked: root.remove()
        }
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        color: root.highlighted ? GeminiStyles.highlightColor : GeminiStyles.geminiThirdColor
    }
}
