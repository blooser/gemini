import QtQuick 2.14

import com.gemini.enums 0.1

Item {
    id: root

    Shortcut {
        sequence: "CTRL+RIGHT"
        onActivated: sessionController.swipeRight()
    }

    Shortcut {
        sequence: "CTRL+LEFT"
        onActivated: sessionController.swipeLeft()
    }

    Shortcut {
        sequence: "CTRL+S"
        onActivated: objectController.openDialog(Enums.Dialog.SwitchDialog, {}, null)
    }

    Shortcut {
        sequence: "S"
        onActivated: sessionController.togglePlayer()
    }

    Shortcut {
        sequence: "M"
        onActivated: sessionController.switchAudioMute()
    }
}
