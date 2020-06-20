import QtQuick 2.14

import QtGraphicalEffects 1.0

import com.gemini.styles 0.1
import com.gemini.common 0.1

Image {
    id: root

    cache: false

    WallpaperInfo {
        resolution: "%1 x %2".arg(root.implicitWidth).arg(root.implicitHeight)
        fileSize: Utility.fileSize(root.source)

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            bottomMargin: GeminiStyles.nMargin
        }
    }

    WallpaperCloseButton {
        anchors {
            right: root.right
            rightMargin: -(width/2)
            top: root.top
            topMargin: -(height/2)
        }
    }

    RectangularGlow {
        anchors.fill: root
        z: root.z - 1
        glowRadius: GeminiStyles.bMargin
        spread: 0.25
        color: GeminiStyles.highlightColor
        cornerRadius: glowRadius
    }
}
