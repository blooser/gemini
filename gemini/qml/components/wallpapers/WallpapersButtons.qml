import QtQuick 2.14
import QtQuick.Layouts 1.12

import Qt.labs.platform 1.0

import com.gemini.helper 0.1
import com.gemini.enums 0.1
import com.gemini.styles 0.1

import "../../items" as Items

Item {
    id: root

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        Items.GImageButton {
            Layout.preferredWidth: 100
            Layout.alignment: Qt.AlignHCenter

            iconSource: "qrc:/icons/plus"

            onClicked: objectController.openDialog(Enums.Dialog.FileOpenDialog, {"title": "Add new wallpapers",
                                                                                 "nameFilters": ["Images (*.png *.jpg *.jpeg)"],
                                                                                 "folder": StandardPaths.writableLocation(StandardPaths.PicturesLocation)}, function(files){
                dataController.insertData(Helper.toStringList(files), Enums.Data.Wallpapers)
            })
        }
    }
}
