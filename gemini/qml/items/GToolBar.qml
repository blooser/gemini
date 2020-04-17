import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.12

import com.gemini.styles 0.1


ToolBar {
    id: root

    property alias backgroundColor: backgroundRect.color

    property alias leftContent: leftContent.data
    property alias middleContent: middleContent.data
    property alias rightContent: rightContent.data

    background: Rectangle {
        id: backgroundRect

        implicitHeight: 40
        color: GeminiStyles.geminiBaseColor
    }

    RowLayout {
        id: mainLayout

        anchors {
            fill: parent
            margins: GeminiStyles.tMargin
        }

        RowLayout {
            id: leftContent

            Layout.minimumWidth: implicitWidth
            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            Layout.fillWidth: leftContent.data.length
        }

        Item { // NOTE: Helps to center middle content
            Layout.minimumWidth: 0
            Layout.fillWidth: true
            Layout.maximumWidth: visible ? Math.max(rightContent.implicitWidth - leftContent.implicitWidth, 0) : 0
        }

        RowLayout {
            id: middleContent
            Layout.minimumWidth: implicitWidth
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
        }

        Item { // NOTE: Helps to center middle content
            Layout.minimumWidth: 0
            Layout.fillWidth: true
            Layout.maximumWidth: visible ? Math.max(leftContent.implicitWidth - rightContent.implicitWidth, 0) : 0

        }

        RowLayout {
            id: rightContent
            Layout.minimumWidth: implicitWidth
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.fillWidth: rightContent.data.length
        }
    }
}
