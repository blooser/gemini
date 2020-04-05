import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../items" as Items

Item {
    id: root

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        Items.GText {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop

            font.pixelSize: GeminiStyles.hFontPixelSize
            text: qsTr("You have unfinished pending process\nDo you want to retry?")
        }

        UnfinishedPendingItems {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
