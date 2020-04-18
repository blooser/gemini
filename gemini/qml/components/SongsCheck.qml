import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.tools 0.1
import com.gemini.enums 0.1
import com.gemini.styles 0.1

import "../items" as Items

Item {
    id: root

    property var selectedSongs: []

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        anchors.fill: parent

        RowLayout {
            spacing: GeminiStyles.tMargin

            Items.GInput {
                id: inputStringFilter
                placeholderText: qsTr("Find a song")
                Layout.fillWidth: true
            }

            Items.GButton {
                text: qsTr("Select all")
                font {
                    capitalization: Font.MixedCase
                    pixelSize: GeminiStyles.sFontPixelSize
                }
                onClicked: songs.selectAll()
            }
        }

        ListView {
            id: songs

            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true

            function selectAll() {
                for (var index=0; index<songs.count; ++index) {
                    var item = itemAtIndex(index)

                    if (item.enabled && !item.checked && item.visible) {
                        item.toggle()
                    }
                }
            }

            model: StringFilterProxyModel {
                sourceModel: songModel
                role: "title"
                string: inputStringFilter.text
            }

            delegate: Items.GCheckBox {
                text: title

                enabled: !dataController.containsData({"playlist": sessionController.currentPlaylist.id,
                                                       "song": id}, Enums.Data.Relations)

                property int indexInSelectedSongs: selectedSongs.findIndex(songId => songId === id)

                onCheckedChanged: {
                    if (checked && indexInSelectedSongs === -1) { // NOTE: Avoid before inserting duplicates
                        selectedSongs.push(id)
                    } else if (!checked) {
                        selectedSongs.splice(indexInSelectedSongs, 1)
                    }

                    root.selectedSongsChanged()
                }

                Component.onCompleted: {
                    if (indexInSelectedSongs !== -1) {
                        checked = true
                    }
                }
            }
        }
    }
}
