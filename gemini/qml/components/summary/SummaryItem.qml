import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

Item {
    id: root

    property alias number: summaryNumber.number
    property alias numberBackgroundColor: summaryNumber.color

    property alias text: summaryText.text
    property alias textBackgroundColor: summaryText.color

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout

        anchors.fill: parent
        spacing: GeminiStyles.tMargin

        SummaryNumber {
            id: summaryNumber
        }

        SummaryText {
            id: summaryText
        }
    }
}
