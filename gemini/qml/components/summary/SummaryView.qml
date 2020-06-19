import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

Item {
    id: root

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        anchors.fill: parent
        spacing: GeminiStyles.tMargin

        SummaryHeader {
            Layout.alignment: Qt.AlignHCenter
        }

        SummaryItems {
            Layout.alignment: Qt.AlignHCenter
        }

        SummaryHelpButton {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 72
            Layout.preferredHeight: 72
        }
    }
}
