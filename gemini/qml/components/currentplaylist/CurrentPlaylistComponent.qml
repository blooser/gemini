import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1
import com.gemini.tools 0.1
import com.gemini.enums 0.1

import "../../items" as Items

Item {
    id: root

    signal songSelected(url song)

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        spacing: GeminiStyles.tMargin

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        CurrentPlaylistSwitcher {
            id: playlistSwitcher

            Layout.fillWidth: true
        }

        CurrentPlaylistSongs {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
