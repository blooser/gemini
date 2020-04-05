import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../components/separator" as Separator
import "../../items" as Items

Rectangle {
    id: root

    property alias icon: swtichPageIcon.icon
    property alias text: switchPageText.text

    property bool current: false

    signal clicked()

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    color: current ? GeminiStyles.highlightColor
                   : switchPageItemMouseArea.containsMouse ? GeminiStyles.geminiThirdColor : GeminiStyles.geminiSecondColor

    radius: GeminiStyles.tMargin

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        spacing: GeminiStyles.bMargin

        SwitchPageIcon {
            id: swtichPageIcon

            current: root.current

            Layout.preferredWidth: 32
            Layout.preferredHeight: 32
        }

        SwitchPageText {
            id: switchPageText

            current: root.current

            Layout.fillWidth: true
        }
    }

    MouseArea {
        id: switchPageItemMouseArea

        enabled: !root.current

        anchors.fill: parent
        hoverEnabled: true

        onClicked: root.clicked()
    }

    Behavior on color {
        ColorAnimation { duration: GeminiStyles.quickAnimation }
    }
}
