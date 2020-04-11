import QtQuick 2.14

import com.gemini.styles 0.1

import "../items/headers" as Headers

Headers.TextHeader {
    id: root

    property var song

    header: song.title
    text: song.artist

    headerHorizontalAlignment: Text.AlignLeft
    horizontalAlignment: Text.AlignLeft
}
