import QtQuick 2.14

import com.gemini.styles 0.1

import "../../items" as Items

Items.GText {
    id: root

    signal songSelected()

    property bool current: false

    horizontalAlignment: Text.AlignLeft

    color: current ? GeminiStyles.highlightColor : GeminiStyles.geminiTextBaseColor

    MouseArea {
        anchors.fill: parent
        onClicked: root.songSelected()
    }
}
