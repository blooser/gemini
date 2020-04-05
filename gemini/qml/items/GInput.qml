import QtQuick 2.14
import QtQuick.Controls 2.12

import com.gemini.styles 0.1

TextField {
    id: root

    property alias radius: rectBackground.radius

    color: GeminiStyles.geminiTextBaseColor

    background: Rectangle {
        id: rectBackground

        implicitWidth: GeminiStyles.controlImplicitWidth
        implicitHeight: GeminiStyles.controlImplicitHeight
        color: GeminiStyles.geminiBaseColor
        radius: GeminiStyles.tMargin
        border {
            width: GeminiStyles.borderBoldWidth
            color: GeminiStyles.geminiSecondColor
        }
    }
}
