import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../items" as Items

Item {
    id: root

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout

        anchors.fill: parent
        spacing: GeminiStyles.nMargin

        Image {
            Layout.preferredWidth: 164
            Layout.preferredHeight: 164

            source: "qrc:/icons/gemini"
            fillMode: Image.PreserveAspectFit
        }

        Items.GText {
            Layout.fillWidth: true
            text: Qt.application.name
            font.pixelSize: GeminiStyles.summaryHeaderPixelSize
        }

        Items.GText {
            text: Qt.application.version
            verticalAlignment: Text.AlignBottom
            font.pixelSize: GeminiStyles.hFontPixelSize
        }
    }
}
