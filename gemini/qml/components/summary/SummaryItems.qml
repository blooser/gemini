import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

Item {
    id: root

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    readonly property var summaryItemsData: [
        {
            "summaryNumber": songModel.size,
            "summaryNumberBackgroundColor": "#ff9933",
            "summaryText": qsTr("Songs"),
            "summaryTextBackgroundColor": "#ff8000"
        },

        {
            "summaryNumber": playlistModel.size,
            "summaryNumberBackgroundColor": "#33ccff",
            "summaryText": qsTr("Playlists"),
            "summaryTextBackgroundColor": "#00bfff"
        },

        {
            "summaryNumber": wallpaperModel.size,
            "summaryNumberBackgroundColor": "#4747d1",
            "summaryText": qsTr("Wallpapers"),
            "summaryTextBackgroundColor": "#3333cc"
        }
    ]

    RowLayout {
        id: mainLayout

        anchors.fill: parent
        spacing: GeminiStyles.hMargin

        Repeater {
            model: summaryItemsData

            SummaryItem {
                number: modelData.summaryNumber
                numberBackgroundColor: modelData.summaryNumberBackgroundColor
                text: modelData.summaryText
                textBackgroundColor: modelData.summaryTextBackgroundColor
            }
        }
    }
}
