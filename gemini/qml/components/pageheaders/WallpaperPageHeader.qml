import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1
import com.gemini.common 0.1
import com.gemini.helper 0.1

import "../../items" as Items
import ".." as Components

Items.GToolBar {
    id: root

    signal addWallpapers()
    signal changeInterval()
    signal removeSelectedWallpapers()

    property var selectedWallpapers: []

    middleContent: RowLayout {
        Items.GToolButton {
            text: qsTr("Add wallpapers")

            onClicked: root.addWallpapers()
        }

        Items.GToolButton {
            text: qsTr("Interval")

            onClicked: root.changeInterval()

            Items.GText {
                anchors {
                    bottom: parent.bottom
                    bottomMargin: GeminiStyles.separatorWidth
                    left: parent.left
                    right: parent.right
                }

                font.pixelSize: GeminiStyles.wallpaperToolButtonIntervalFontSize

                text: Utility.formatTime(sessionController.wallpaperInterval, Helper.extraHumanTimeFormat(sessionController.wallpaperInterval))
            }
        }

        Items.GToolButton {
            id: removeSelectedWallpapersToolButton

            text: qsTr("Remove %1 wallpapers").arg(selectedWallpapers.length)

            onClicked: root.removeSelectedWallpapers()

            state: "hidden"

            states: [
                State {
                    name: "hidden"
                    when: !selectedWallpapers.length
                    PropertyChanges { target: removeSelectedWallpapersToolButton; implicitWidth: GeminiStyles.none; implicitHeight: GeminiStyles.none; opacity: GeminiStyles.hidden }
                }
            ]

            transitions: [
                Transition {
                    from: "hidden"; to: "*"
                    SequentialAnimation {
                        NumberAnimation { properties: "implicitWidth, implicitHeight"; duration: GeminiStyles.quickAnimation }
                        NumberAnimation { property: "opacity"; duration: GeminiStyles.quickAnimation }
                    }
                },

                Transition {
                    from: "*"; to: "hidden"
                    SequentialAnimation {
                        NumberAnimation { property: "opacity"; duration: GeminiStyles.quickAnimation }
                        NumberAnimation { properties: "implicitWidth, implicitHeight"; duration: GeminiStyles.quickAnimation }
                    }
                }
            ]
        }
    }

    rightContent: Components.Label {
        iconSource: "qrc:/icons/image"
        text: wallpaperModel.size
        opacity: wallpaperModel.size ? GeminiStyles.opacityVisible : GeminiStyles.opacityHidden

        Behavior on opacity {
            OpacityAnimator { duration: GeminiStyles.quickAnimation }
        }
    }
}
