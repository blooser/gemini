import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

Item {
    id: root

    implicitWidth: items.implicitWidth
    implicitHeight: items.implicitHeight

    ListView {
        id: items

        anchors.fill: parent

        clip: true
        spacing: GeminiStyles.bMargin

        model: pendingModel

        delegate: UnfinishedPendingItem {
            width: items.width
            text: url
        }
    }
}
