import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../items" as Items

Items.GToolBar {
    id: root

    signal addWallpapers()

    implicitWidth: mainLayout.implicitWidth

    RowLayout {
        id: mainLayout

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        Items.GToolButton {
            Layout.alignment: Qt.AlignHCenter

            text: qsTr("Add wallpapers")

            onClicked: root.addWallpapers()
        }
    }
}
