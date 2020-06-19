import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import ".." as Components

Item {
    id: root

    implicitWidth: listView.implicitWidth
    implicitHeight: listView.implicitHeight

    TableView {
        id: listView

        readonly property var columnWidth: [200, 500]
        columnWidthProvider: function (column) {
            return columnWidth[column]
        }

        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds

        columnSpacing: GeminiStyles.tMargin
        rowSpacing: GeminiStyles.tMargin

        clip: true
        model: SummaryShortcutModel {}

        delegate: Components.TileText {
            text: display
        }
    }
}
