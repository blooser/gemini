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

        main: GridView {
            id: gridView

            model: wallpaperModel

            cellWidth: 180; cellHeight: 180

            currentIndex: -1
            highlight: Components.Highlight {}

            delegate: WallpaperItem {
                width: 150; height: 150

                readonly property bool current: (source == sessionController.currentWallpaper)

                onCurrentChanged: {
                    if (current) {
                        gridView.currentIndex = index
                    }
                }

                source: Helper.localFile(url)

                onExpand: objectController.openDialog(Enums.Dialog.WallpaperDialog, {"source": Helper.localFile(url)}, null)
                onRemove: objectController.openDialog(Enums.Dialog.ConfirmDialog, {"text": qsTr("Are you sure you want to delete the wallpaper?")}, function(){
                    dataController.removeData([{"id": id, "url": url}], Enums.Data.Wallpapers)
                })
            }
        }

        replace: Components.TileText {
            text: qsTr("Click above button and fill your wallpaper board")
            radius: GeminiStyles.tMargin
        }

        when: (wallpaperModel.size === GeminiStyles.empty)
    }
}
