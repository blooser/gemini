import QtQuick 2.14

import com.gemini.styles 0.1

Rectangle {
    id: root

    property alias icon: icon.source

    property bool current: false

    color:  current ? GeminiStyles.highlightColor : GeminiStyles.geminiThirdColor
    radius: GeminiStyles.tMargin

    Image {
        id: icon

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        fillMode: Image.PreserveAspectFit
    }
}
