import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import ".." as Components
import "../../items" as Items

Item {
    id: root

    property alias text: textItem.text

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        spacing: GeminiStyles.bMargin

        Components.Icon {
            Layout.preferredWidth: 32
            Layout.preferredHeight: 32

            iconSource: "qrc:/icons/burn"
        }

        Items.GText {
            id: textItem

            Layout.fillWidth: true

            color: GeminiStyles.unfinishedColor
            font.pixelSize: GeminiStyles.bFontPixelSize
            elide: Text.ElideLeft
            horizontalAlignment: Text.AlignLeft
        }
    }
}
