import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1
import com.gemini.styles 0.1

import "../components/switchpage" as SwitchPage

GDialog {
    id: root

    implicitWidth: 450
    implicitHeight: 250

    dialog: Enums.Dialog.SwitchDialog
    headerText: qsTr("Switch page")

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    ColumnLayout {
        id: mainLayout

        anchors.fill: parent

        Repeater {
            model: sessionController.pages

            SwitchPage.SwitchPageItem {
                Layout.fillWidth: true

                icon: modelData.icon
                text: modelData.name

                current: (sessionController.currentPageIndex === index)

                onClicked: {
                    sessionController.swipe(index)
                    root.accept()
                }
            }
        }
    }
}
