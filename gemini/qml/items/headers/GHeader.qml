import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import ".." as Items

Item {
    id: root

    property alias header: headerText.text
    property alias headerHorizontalAlignment: headerText.horizontalAlignment

    default property alias content: mainLayout.data

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        anchors.fill: parent

        spacing: GeminiStyles.tMargin

        Items.GText {
            id: headerText
            Layout.fillWidth: true
            font.pixelSize: GeminiStyles.hFontPixelSize
            wrapMode: Text.WordWrap
        }
    }
}
