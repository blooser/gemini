import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1
import com.gemini.helper 0.1

import "../../items" as Items
import ".." as Components

Item {
    id: root

    property alias songs: songsLabel.text
    property alias duration: durationLabel.text

    implicitWidth: mainLayout.implicitWidth + 15
    implicitHeight: mainLayout.implicitHeight + 10

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        spacing: GeminiStyles.tMargin

        PlaylistLabel {
            id: songsLabel

            iconSource: "qrc:/icons/music"
            hiddenOn: (text === "0")

        }

        PlaylistLabel {
            id: durationLabel

            iconSource: "qrc:/icons/time"
            hiddenOn: (text === "00:00" || text === "")
        }
    }
}
