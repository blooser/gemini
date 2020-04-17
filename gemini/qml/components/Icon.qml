import QtQuick 2.14

import com.gemini.styles 0.1

Rectangle {
    id: root

    property alias iconSource: image.source

    radius: GeminiStyles.tMargin
    color: GeminiStyles.geminiSecondColor

    implicitWidth: image.implicitWidth
    implicitHeight: image.implicitHeight

    Image {
        id: image

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        fillMode: Image.PreserveAspectFit
    }
}
