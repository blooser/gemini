import QtQuick 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import com.gemini.styles 0.1

import "../../items" as Items

Item {
    id: root

    property alias source: image.source

    signal expand()
    signal remove()

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        Image {
            id: image

            Layout.fillWidth: true
            Layout.fillHeight: true

            fillMode: Image.Stretch
            asynchronous: true
        }

        WallpaperItemButtons {
            Layout.fillWidth: true

            onExpand: root.expand()
            onRemove: root.remove()
        }
    }

    Items.GBusyIndicator {
        readonly property bool loadingImage: (image.status === Image.Loading)
        anchors.centerIn: parent
        running: loadingImage
        visible: loadingImage
    }
}


