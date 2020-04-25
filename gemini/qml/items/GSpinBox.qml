import QtQuick 2.14
import QtQuick.Controls 2.14

import com.gemini.styles 0.1

SpinBox {
    id: root

    contentItem: TextInput {
        z: 2
        font: root.font
        text: root.textFromValue(root.value, root.locale)
        color: GeminiStyles.geminiTextBaseColor
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        readOnly: !root.editable
        validator: root.validator
    }

    up.indicator: Rectangle {
        x: root.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 40
        implicitHeight: 40
        color: root.up.pressed ? GeminiStyles.highlightColor : GeminiStyles.geminiThirdColor

        Image {
            anchors.centerIn: parent
            width: 24
            height: 24
            source: "qrc:/icons/plus"
        }
    }

    down.indicator: Rectangle {
        x: root.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 40
        implicitHeight: 40
        color: root.down.pressed ? GeminiStyles.highlightColor : GeminiStyles.geminiThirdColor

        Image {
            anchors.centerIn: parent
            width: 24
            height: 24
            source: "qrc:/icons/minus"
        }
    }

    background: null
}
