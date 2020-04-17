import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.enums 0.1
import com.gemini.styles 0.1

Rectangle {
    id: root

    property int orientation: Qt.Horizontal

    color: GeminiStyles.geminiThirdColor

    state: "horizontal"
    states: [
        State {
            name: "horizontal"
            when: (orientation === Qt.Horizontal)
            PropertyChanges { target: root; Layout.fillWidth: true; Layout.preferredHeight: GeminiStyles.separatorWidth; Layout.bottomMargin: GeminiStyles.nMargin }

        },

        State {
            name: "vertical"
            when: (orientation === Qt.Vertical)
            PropertyChanges { target: root; Layout.fillHeight: true; Layout.preferredWidth: GeminiStyles.separatorWidth; Layout.bottomMargin: GeminiStyles.nMargin }
        }
    ]
}
