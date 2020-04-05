import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1
import com.gemini.styles 0.1

import "../items" as Items
import "separator" as Separator

Item {
    id: root

    property alias header: textItem.text

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        spacing: GeminiStyles.tMargin

        Items.GText {
            id: textItem

            Layout.fillWidth: true

            font.pixelSize: GeminiStyles.hFontPixelSize
        }

        Separator.LineSeparator {

        }
    }
}
