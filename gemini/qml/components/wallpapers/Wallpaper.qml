import QtQuick 2.14
import QtGraphicalEffects 1.0

import com.gemini.styles 0.1

Item {
    id: root

    property string source

    onSourceChanged: {
        backImage.source = frontImage.source
        backImage.opacity = GeminiStyles.visible

        frontImage.opacity = GeminiStyles.hidden
        frontImage.source = source
    }

    ParallelAnimation {
        id: changeWallpaperAnimation
        running: (frontImage.opacity !== GeminiStyles.visible)
        OpacityAnimator { target: frontImage; from: GeminiStyles.hidden; to: GeminiStyles.visible; duration: GeminiStyles.slowAnimation }
        OpacityAnimator { target: backImage; from: GeminiStyles.visible; to: GeminiStyles.hidden; duration: GeminiStyles.slowAnimation }
    }

    Image {
        id: frontImage

        cache: false

        anchors.fill: parent
        fillMode: Image.Stretch
    }

    Image {
        id: backImage

        cache: false

        anchors.fill: parent
        fillMode: Image.Stretch
    }
}
