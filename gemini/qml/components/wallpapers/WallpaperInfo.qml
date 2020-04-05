import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1
import com.gemini.common 0.1

import "../../items" as Items

Item {
    id: root

    property alias resolution: resolution.text
    property alias fileSize: fileSize.text

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        spacing: GeminiStyles.none

        Items.GText {
            id: resolution

            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: GeminiStyles.bFontPixelSize
        }

        Items.GText {
            id: fileSize
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: GeminiStyles.bFontPixelSize
        }
    }
}

