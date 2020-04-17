import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../items" as Items

Rectangle {
    id: root

    property alias iconSource: icon.source
    property alias text: tileText.text
    property alias font: tileText.font

    implicitWidth: mainLayout.implicitWidth + GeminiStyles.bMargin
    implicitHeight: mainLayout.implicitHeight + GeminiStyles.nMargin

    color: GeminiStyles.geminiSecondColor
    radius: GeminiStyles.tMargin

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        spacing: GeminiStyles.tMargin

        Image {
            id: icon

            Layout.preferredWidth: 18
            Layout.preferredHeight: 18
            Layout.alignment: Qt.AlignHCenter

            fillMode: Image.PreserveAspectFit
        }

        Items.GText {
            id: tileText

            font {
                pixelSize: GeminiStyles.sFontPixelSize
                family: GeminiStyles.numberFontFamily
            }

            horizontalAlignment: Text.AlignLeft
        }
    }
}
