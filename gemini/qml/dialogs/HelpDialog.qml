import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1

import "../components/summary" as Summary

GDialog {
    id: root

    implicitHeight: 370
    implicitWidth: 700

    dialog: Enums.Dialog.HelpDialog
    headerText: qsTr("Help")
    standardButtons: Dialog.Ok

    contentItem: Summary.SummaryShortcuts {}
}
