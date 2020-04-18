import QtQuick 2.14
import QtQuick.Layouts 1.12

import com.gemini.tools 0.1
import com.gemini.enums 0.1

import "../items" as Items

Item {
    id: root

    property var selectedSongs: []

    implicitWidth: mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        anchors.fill: parent

        Items.GInput {
            id: inputStringFilter
            Layout.fillWidth: true
        }

        ListView {
            id: songs

            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true

            model: StringFilterProxyModel {
                sourceModel: songModel
                role: "title"
                string: inputStringFilter.text
            }

            delegate: Items.GCheckBox {
                text: title

                enabled: !dataController.containsData({"playlist": sessionController.currentPlaylist.id,
                                                       "song": id}, Enums.Data.Relations)

                onCheckStateChanged: {
                    if (checkState === Qt.Checked) {
                        selectedSongs.push(id)
                    } else if (checkState === Qt.Unchecked) {
                        selectedSongs.splice(selectedSongs.indexOf(id), 1)
                    }

                    root.selectedSongsChanged()
                }

                Component.onDestruction: selectedSongs.splice(selectedSongs.indexOf(id), 1)
            }
        }
    }
}
