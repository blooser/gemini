import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Window 2.14
import QtGraphicalEffects 1.0

import com.gemini.styles 0.1

import "../components/wallpapers" as Wallpapers

GPage {
    id: root

    property alias wallpaper: wallpaper.source
    property alias blurred: fastBlurr.visible


    Wallpapers.Wallpaper {
        id: wallpaper
        anchors.fill: parent
    }

    FastBlur {
        id: fastBlurr
        visible: false
        anchors.fill: wallpaper
        source: wallpaper
        radius: 64
    }
}
