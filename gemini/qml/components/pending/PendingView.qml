import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1

import "../../items" as Items

Item {
    id: root

    implicitWidth: pendingView.implicitWidth
    implicitHeight: pendingView.implicitHeight

    ListView {
        id: pendingView

        boundsBehavior: Flickable.StopAtBounds
        clip: true
        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        model: pendingModel

        delegate: PendingItem {
            width: pendingView.width

            text: name
            pending: !done
            textColor: done ? GeminiStyles.highlightColor : GeminiStyles.geminiTextBaseColor

            onPendingChanged: {
                if (!pending) {
                    pendingView.currentIndex = index
                }
            }
        }
    }
}
