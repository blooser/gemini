import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../items" as Items

Item {
    id: root

    property bool current: false

    property alias text: textItem.text

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        Items.GText {
            id: textItem

            Layout.fillWidth: true

            horizontalAlignment: Text.AlignLeft
            font.pixelSize: GeminiStyles.hFontPixelSize
        }

        Items.GText {
            text: qsTr("Current")

            visible: root.current

            rightPadding: GeminiStyles.tMargin
            font.pixelSize: GeminiStyles.tFontPixelSize
            horizontalAlignment: Text.AlignRight

            style: Text.Outline
            styleColor: GeminiStyles.geminiSecondColor
        }
    }
}
