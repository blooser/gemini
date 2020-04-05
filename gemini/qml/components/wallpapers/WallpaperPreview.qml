import QtQuick 2.14

import com.gemini.styles 0.1

Item {
    id: root

    property alias source: image.source

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
