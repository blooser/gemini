import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Window 2.14

import com.gemini.enums 0.1
import com.gemini.tools 0.1
import com.gemini.helper 0.1

import "pages" as Pages
import "components" as Components
import "items" as Items

Window {
    id: root

    title: "Gemini"
    visible: true

    width: GeminiStyles.mainWindowWidth
    height: GeminiStyles.mainWindowHeight

    Components.Shortcuts {
        // Comfort
    }

    Picker {
        id: picker
        model: wallpaperModel
        roleName: "url"
        interval: 10000
        running: (wallpaperModel.size > GeminiStyles.empty)

        onPicked: sessionController.currentWallpaper = data
    }

    Connections {
        target: sessionController

        onSwipeLeft: swipeView.decrementCurrentIndex()
        onSwipeRight: swipeView.incrementCurrentIndex()
        onSwipe: swipeView.setCurrentIndex(index)
    }

    Binding {
        target: songsInRelations
        property: "currentPlaylist"
        value: sessionController.currentPlaylist
    }

    SwipeView {
        id: swipeView

        anchors.fill: parent

        onCurrentIndexChanged: sessionController.currentPageIndex = currentIndex

        Pages.SummaryPage {
            wallpaper: sessionController.currentWallpaper
            blurred: true
        }

        Pages.MusicPage {
            wallpaper: sessionController.currentWallpaper
        }

        Pages.PlaylistPage {

        }

        Pages.WallpaperPage {

        }

        Component.onCompleted: {
            currentIndex = sessionController.currentPageIndex
        }
    }

    Connections {
        target: objectController

        onOpen: objectCreator.create(url, properties, callback)
        onClose: objectCreator.remove(dialog)
    }

    QtObject {
        id: objectCreator

        property var stack: []

        function create(url, properties, callback) {
            var component = Qt.createComponent(url)

            if (component.status === Component.Error) {
                console.warn("Error while creating object", component.errorString())
                return
            }

            if (typeof callback === "function") {
                properties["callback"] = callback
            }

            var object = component.createObject(root, properties)
            console.log("Open", object)
            stack.push(object)
            object.open()
        }

        function remove(dialog) {
            const dialogToRemove = stack.find(item => item.dialog === dialog)

            if (dialogToRemove !== undefined) {
                console.log("Close", dialogToRemove)
                stack = stack.filter(item => item.dialog !== dialogToRemove.dialog)
                dialogToRemove.close()
                dialogToRemove.destroy()
            }
        }
    }

    Component.onCompleted: {
        if (sessionController.unfinishedPeding) {
            objectController.openDialog(Enums.Dialog.UnfinishedPendingDialog, {}, null)
        }
    }
}


