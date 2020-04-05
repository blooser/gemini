import QtQuick 2.14
import QtQuick.Layouts 1.0

import com.gemini.styles 0.1

import "../../items" as Items

Item {
    id: root

    signal expand()
    signal remove()

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        spacing: GeminiStyles.tMargin

        Items.GImageButton {
            Layout.preferredWidth: 32
            Layout.preferredHeight: 32
            Layout.alignment: Qt.AlignRight

            iconSource: "qrc:/icons/expand"

            onClicked: root.expand()
        }

        Items.GImageButton {
            Layout.preferredWidth: 32
            Layout.preferredHeight: 32
            Layout.alignment: Qt.AlignLeft

            iconSource: "qrc:/icons/delete"

            onClicked: root.remove()
        }
    }
}
