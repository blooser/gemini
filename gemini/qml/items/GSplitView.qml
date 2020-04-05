import QtQuick 2.14
import QtQuick.Controls 2.14

import com.gemini.styles 0.1

SplitView {
    id: root

    anchors {
        fill: parent
        margins: GeminiStyles.tMargin
    }

    handle: Rectangle {
        implicitWidth: 6
        implicitHeight: 6
        color: SplitHandle.pressed ? GeminiStyles.highlightColor
                                   : (SplitHandle.hovered ? GeminiStyles.geminiThirdColor : GeminiStyles.geminiSecondColor)

        Behavior on color {
            ColorAnimation { duration: GeminiStyles.quickAnimation }
        }
    }
}
