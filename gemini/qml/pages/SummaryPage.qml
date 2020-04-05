import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Window 2.14

import com.gemini.styles 0.1

import "../components" as Components
import "../components/summary" as Summary

GWallpaperPage {
    id: root

    Summary.SummaryView {
        anchors {
            fill: parent
            margins: GeminiStyles.hMargin
        }
    }
}
