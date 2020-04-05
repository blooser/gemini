import QtQuick 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import com.gemini.styles 0.1

import "../../components/pending" as Pending
import "../../items" as Items

Item {
    id: root

    property alias pending: pendingProcess.processing
    property alias text: textItem.text
    property alias textColor: textItem.color

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        spacing: GeminiStyles.bMargin

        Pending.PendingProcess {
            id: pendingProcess

            Layout.preferredWidth: 64
            Layout.preferredHeight: 64
        }

        Items.GText {
            id: textItem

            Layout.fillWidth: true

            font.pixelSize: GeminiStyles.bFontPixelSize
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideLeft
        }
    }
}
