import QtQuick 2.14
import QtQuick.Controls 2.14

import com.gemini.styles 0.1

ToolBar {
    id: root

    property alias backgroundColor: backgroundRect.color

    background: Rectangle {
        id: backgroundRect

        implicitHeight: 40
        color: GeminiStyles.geminiBaseColor
    }
}
