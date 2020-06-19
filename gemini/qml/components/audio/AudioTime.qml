import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1
import com.gemini.common 0.1

import "../../items" as Items

Item {
    id: root

    property int totalTime
    property int time

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        anchors.fill: parent
        spacing: GeminiStyles.tMargin

        Items.GText {
            id: totalTimeText

            Layout.fillWidth: true

            text: Utility.formatTime(totalTime, "mm:ss")
            color: GeminiStyles.highlightColor
            font.pixelSize: GeminiStyles.nFontPixelSize
        }

        Items.GText {
            Layout.fillWidth: true

            text: Utility.formatTime(time, "mm:ss")
            color: GeminiStyles.highlightColor

            font {
                pixelSize: GeminiStyles.hFontPixelSize
                bold: true
            }
        }
    }

    states: State {
        when: (totalTime === GeminiStyles.invalid)
        PropertyChanges { target: totalTimeText; font.pixelSize: 0 }
    }

    transitions: Transition {
        NumberAnimation {
            property: "font.pixelSize"
            duration: GeminiStyles.quickAnimation
        }
    }
}
