import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1
import com.gemini.tools 0.1
import com.gemini.enums 0.1

import "../../items" as Items
import "../dynamic" as Dynamic

Item {
    id: root

    implicitWidth: changer.implicitWidth
    implicitHeight: changer.implicitHeight

    Dynamic.Changer {
        id: changer

        anchors.fill: parent

        main: CurrentPlaylistComponent {}
        replace: CurrentPlaylistNew {}
        when: (playlistModel.size === GeminiStyles.empty)
    }
}
