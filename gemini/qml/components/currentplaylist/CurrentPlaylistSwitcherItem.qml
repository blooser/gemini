import QtQuick 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import com.gemini.styles 0.1

import "../../items" as Items

Rectangle {
    id: root

    property alias text: textItem.text

    signal remove()
    signal clicked()

    implicitWidth: mainLayout.implicitWidth + mainLayout.fullMargin
    implicitHeight: mainLayout.implicitHeight + mainLayout.fullMargin

    color: itemMouseArea.containsMouse ? GeminiStyles.geminiSecondColor : GeminiStyles.geminiBaseColor
    radius: 3

    RowLayout {
        id: mainLayout

        readonly property int fullMargin: 3 * 4

        anchors {
            fill: parent
            margins: 3
        }

        Items.GText {
            id: textItem

            Layout.fillWidth: true
        }

        Items.GImageButton {
            id: removeButton

            Layout.preferredWidth: 32
            Layout.preferredHeight: 32

            iconSource: "qrc:/icons/delete"

            onClicked: root.remove()
        }
    }

    MouseArea {
        id: itemMouseArea

        z: removeButton.z - 1
        anchors.fill: parent
        hoverEnabled: true

        onClicked: root.clicked()
    }
}
