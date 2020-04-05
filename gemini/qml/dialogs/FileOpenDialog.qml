import QtQuick 2.14
import QtQuick.Dialogs 1.3

import com.gemini.enums 0.1

FileDialog {
    id: root

    property var callback
    property int dialog: Enums.Dialog.FileOpenDialog

    selectMultiple: true

    onAccepted: callback(fileUrls)
}
