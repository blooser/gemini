import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

Item {
    id: root

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    GridLayout {
        id: mainLayout

        columns: 2

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        SummaryItem {
            Layout.column: 0
            Layout.row: 0
            Layout.alignment: Qt.AlignHCenter

            number: songModel.size
            numberBackgroundColor: "#ff9933"

            text: qsTr("Songs")
            textBackgroundColor: "#ff8000"
        }

        SummaryItem {
            Layout.column: 1
            Layout.row: 0
            Layout.alignment: Qt.AlignHCenter

            number: playlistModel.size
            numberBackgroundColor: "#33ccff"

            text: qsTr("Playlists")
            textBackgroundColor: "#00bfff"
        }

        SummaryItem {
            Layout.column: 0
            Layout.columnSpan: 2
            Layout.row: 1
            Layout.alignment: Qt.AlignHCenter

            number: wallpaperModel.size
            numberBackgroundColor: "#4747d1"

            text: qsTr("Wallpapers")
            textBackgroundColor: "#3333cc"
        }
    }
}
