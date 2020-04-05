import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1
import com.gemini.styles 0.1

Dialog {
    id: root

    property int dialog: Enums.Dialog.Unknown

    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose

    anchors.centerIn: Overlay.overlay

    Overlay.modal: Rectangle {
        color: "#99000000"

        Behavior on opacity {
            OpacityAnimator { duration: GeminiStyles.quickAnimation }
        }
    }

    background: Rectangle {
        implicitWidth: GeminiStyles.gBaseDialogImplicitWidth
        implicitHeight: GeminiStyles.gBaseDialogImplicitHeight
        color: GeminiStyles.geminiBaseColor
        radius: GeminiStyles.nMargin
    }

    enter: Transition {
        NumberAnimation { property: "opacity"; to: GeminiStyles.visible; duration: GeminiStyles.quickAnimation }
    }

    exit: Transition {
        NumberAnimation { property: "opacity"; to: GeminiStyles.hidden; duration: GeminiStyles.quickAnimation }
    }
}
