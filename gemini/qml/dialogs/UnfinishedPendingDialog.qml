import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1

import "../components/pending" as Pending
import "../items" as Items

GDialog {
    id: root

    implicitWidth: 750
    implicitHeight: 400

    dialog: Enums.Dialog.UnfinishedPendingDialog
    headerText: qsTr("Unfinished pending")
    standardButtons: Dialog.Cancel | Dialog.Retry

    contentItem: Pending.UnfinishedPendingView {}

    onAccepted: {
        dataController.resumeUnfinishedPending()
        sessionController.unfinishedPeding = false
    }
    onRejected: dataController.cancelUnfinishedPending()
}
