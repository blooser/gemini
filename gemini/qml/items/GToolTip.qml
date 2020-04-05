import QtQuick 2.14
import QtQuick.Controls 2.14

import com.gemini.styles 0.1

ToolTip {
    id: root

    contentItem: GText {
        text: root.text
        font: root.font
    }

    background: Rectangle {
        color: GeminiStyles.geminiThirdColor
        radius: GeminiStyles.tMargin
    }

    Behavior on x {
        NumberAnimation { duration: GeminiStyles.toolTipAnimation }
    }

    Behavior on y {
        NumberAnimation { duration: GeminiStyles.toolTipAnimation }
    }
}
