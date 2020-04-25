import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1
import com.gemini.styles 0.1

import "../items" as Items

GDialog {
    id: root

    headerText: qsTr("Wallpaper Interval")
    dialog: Enums.Dialog.WallpaperIntervalDialog
    standardButtons: Dialog.Cancel | Dialog.Ok

    implicitWidth: 350

    contentItem: Items.GSpinBox {
        id: intervalSpinBox

        from: 5000
        stepSize: 1000
        to: 60000

        font.pixelSize: GeminiStyles.hFontPixelSize

        Component.onCompleted: {
            value = sessionController.wallpaperInterval
        }
    }

    onAccepted: callback(intervalSpinBox.value)
}
