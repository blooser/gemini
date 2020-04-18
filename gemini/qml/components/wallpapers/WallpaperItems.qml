import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1
import com.gemini.styles 0.1

import ".." as Components

GridView {
    id: root

    property var selectedWallpapers: []

    model: wallpaperModel

    cellWidth: 180; cellHeight: 180

    currentIndex: -1
    highlight: Components.Highlight {}

    Connections {
        target: sessionController

        onClearSelection: selectedWallpapers = []
    }

    delegate: WallpaperItem {
        width: 150; height: 150

        readonly property bool current: (source == sessionController.currentWallpaper)

        onCurrentChanged: {
            if (current) {
                root.currentIndex = index
            }
        }

        onSelectedChanged: {
            if (selected) {
                selectedWallpapers.push({"id": id, "url": url})
            } else {
                selectedWallpapers.splice(selectedWallpapers.indexOf({"id": id, "url": url}), 1)
            }

            root.selectedWallpapersChanged()
        }

        source: url

        onExpand: objectController.openDialog(Enums.Dialog.WallpaperDialog, {"source": url}, null)
        onRemove: objectController.openDialog(Enums.Dialog.ConfirmDialog, {"text": qsTr("Are you sure you want to delete the wallpaper?")}, function(){
            dataController.removeData([{"id": id, "url": url}], Enums.Data.Wallpapers)
        })

        Component.onDestruction: selected = false
    }
}
