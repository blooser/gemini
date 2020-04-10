import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1
import com.gemini.helper 0.1
import com.gemini.styles 0.1

import ".." as Components
import "../../items" as Items
import "../dynamic" as Dynamic

Rectangle {
    id: root

    implicitWidth: changer.implicitWidth
    implicitHeight: changer.implicitHeight

    color: GeminiStyles.blank
    radius: GeminiStyles.tMargin

    border {
        width: GeminiStyles.borderWidth
        color: GeminiStyles.geminiSecondColor
    }

    Dynamic.Changer {
        id: changer

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        main: WallpaperItems {}

        replace: Components.TileText {
            text: qsTr("Click above button and fill your wallpaper board")
            radius: GeminiStyles.tMargin
        }

        when: (wallpaperModel.size === GeminiStyles.empty)
    }
}
