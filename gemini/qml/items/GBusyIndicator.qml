import QtQuick 2.14
import QtQuick.Controls 2.12

import com.gemini.styles 0.1

BusyIndicator {
    id: root

    property int circleWidth: 10
    property int circleHeight: 10

    readonly property int numberOfCircles: 6

    contentItem: Item {
        id: item

        implicitWidth: 64
        implicitHeight: 64

        width: 64
        height: 64

        opacity: root.running ? GeminiStyles.visible : GeminiStyles.hidden

        RotationAnimator {
            target: item
            running: root.visible && root.running
            from: 0
            to: 360
            loops: Animation.Infinite
            duration: 1500
        }

        Repeater {
            id: repeater

            model: numberOfCircles

            Rectangle {
                x: item.width/2 - width/2
                y: item.height/2 - height/2

                implicitWidth: root.circleWidth
                implicitHeight: root.circleHeight

                radius: GeminiStyles.tMargin
                color: GeminiStyles.highlightColor

                transform: [
                    Translate {
                        y: -Math.min(item.width, item.height) * 0.5 + 5
                    },

                    Rotation {
                        angle: index/repeater.count * 360
                        origin.x: GeminiStyles.tMargin
                        origin.y: GeminiStyles.tMargin
                    }
                ]
            }
        }
    }
}
