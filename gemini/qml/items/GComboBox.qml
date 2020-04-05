import QtQuick 2.14
import QtQuick.Controls 2.12

import com.gemini.styles 0.1

ComboBox {
    id: root

    function togglePopup() {
        root.popup.visible = !root.popup.visible
    }

    delegate: ItemDelegate {
        width: root.width

        contentItem: GText {
            text: root.textRole ? (Array.isArray(root.model) ? modelData[root.textRole] : model[root.textRole]) : modelData
        }

        highlighted: (root.highlightedIndex === index)
    }

    indicator: GInputButton {
        id: inputButton

        width: root.width

        text: root.displayText

        onClicked: root.togglePopup()
    }

    background: Rectangle {
        implicitWidth: GeminiStyles.controlImplicitWidth
        implicitHeight: GeminiStyles.controlImplicitHeight
        color: GeminiStyles.geminiThirdColor
        radius: inputButton.radius
        border {
            width: GeminiStyles.borderWidth
            color: GeminiStyles.geminiBaseColor
        }
    }

    popup: Popup {
        y: root.height - 1
        width: root.width
        implicitHeight:  contentItem.implicitHeight
        padding: 0

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: root.delegateModel
            currentIndex: root.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator {}
        }

        background: Rectangle {
            radius: GeminiStyles.tMargin
            color: GeminiStyles.geminiBaseColor
        }
    }
}
