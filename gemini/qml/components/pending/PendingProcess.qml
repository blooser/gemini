import QtQuick 2.14

import com.gemini.styles 0.1

import ".." as Components
import "../../items" as Items
import "../dynamic" as Dynamic

Item {
    id: root

    property bool processing: true

    implicitWidth: changer.implicitWidth
    implicitHeight: changer.implicitHeight

    Dynamic.Changer {
        id: changer

        anchors {
            fill: parent
            margins: root.processing ? GeminiStyles.none : GeminiStyles.nMargin
        }

        main: Items.GBusyIndicator {
            running: true
        }

        replace: Components.Icon {
            iconSource: "qrc:/icons/check"
        }

        when: !root.processing
    }
}
