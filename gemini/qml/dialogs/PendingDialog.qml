import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1

import "../components/pending" as Pending
import "../items" as Items

GDialog {
    id: root

    implicitWidth: 750
    implicitHeight: 500

    dialog: Enums.Dialog.PendingDialog
    headerText: qsTr("Pending")
    standardButtons: Dialog.NoButton

    contentItem: Pending.PendingView {}

    Connections {
        target: sessionController

        onPendingChanged: {
            if (!pending) {
                close()
            }
        }
    }
}
