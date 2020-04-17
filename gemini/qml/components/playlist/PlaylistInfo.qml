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

    implicitWidth: mainLayout.implicitWidth + GeminiStyles.bMargin
    implicitHeight: mainLayout.implicitHeight + GeminiStyles.nMargin

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        spacing: GeminiStyles.tMargin

        PlaylistLabel {
            id: songsLabel

            Layout.alignment: Qt.AlignRight
            font.family: GeminiStyles.numberFontFamily
            iconSource: "qrc:/icons/music"
            hidden: (text === "0")

        }

        PlaylistLabel {
            id: durationLabel

            font.family: GeminiStyles.numberFontFamily
            iconSource: "qrc:/icons/time"
            hidden: (text === "00:00" || text === "")
        }
    }
}
