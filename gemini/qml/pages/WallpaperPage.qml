import QtQuick 2.14

import Qt.labs.platform 1.1

import com.gemini.helper 0.1
import com.gemini.enums 0.1
import com.gemini.styles 0.1

import "../components/pageheaders" as PageHeaders
import "../components/wallpapers" as Wallpapers

GPage {
    id: root

    header: PageHeaders.WallpaperPageHeader {
        onAddWallpapers: objectController.openDialog(Enums.Dialog.FileOpenDialog, {"title": qsTr("Add new wallpapers"),
                                                                                   "nameFilters": ["Images (*.png *.jpg *.jpeg)"],
                                                                                   "folder": StandardPaths.writableLocation(StandardPaths.PicturesLocation)}, function(files){
            dataController.insertData(Helper.toList(files), Enums.Data.Wallpapers)
        })
    }

    Wallpapers.WallpaperView {
        anchors {
            fill: parent
            margins: GeminiStyles.nMargin
        }
    }
}
