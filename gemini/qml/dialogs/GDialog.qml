import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../items" as Items
import "../components" as Components

import com.gemini.styles 0.1
import com.gemini.enums 0.1
import com.gemini.helper 0.1

GBaseDialog {
    id: root

    property var callback: null
    property bool acceptEnabled: true

    property alias headerText: dialogHeader.header

    header: Components.DialogHeader {
        id: dialogHeader
    }

    footer: DialogButtonBox {
        delegate: Items.GButton {
            Component.onCompleted: {
                if (DialogButtonBox.buttonRole === DialogButtonBox.AcceptRole) {
                    enabled = Qt.binding(function(){
                        return root.acceptEnabled
                    })
                }
            }
        }

        background: null
    }

    onClosed: objectController.close(dialog)
}
