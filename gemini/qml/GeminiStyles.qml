pragma Singleton

import QtQuick 2.14

QtObject {

    /**
    t = tiny
    n = normal
    b = big
    h = huge
    **/

    // MainWindow
    readonly property int mainWindowWidth: 1200
    readonly property int mainWindowHeight: 700

    // Margins
    readonly property int tMargin: 5
    readonly property int nMargin: 10
    readonly property int bMargin: 15
    readonly property int hMargin: 20

    // Font
    readonly property int tFontPixelSize: 12
    readonly property int sFontPixelSize: 14
    readonly property int nFontPixelSize: 16
    readonly property int bFontPixelSize: 20
    readonly property int hFontPixelSize: 24

    readonly property int summaryNumberFontPixelSize: 72

    readonly property string numberFontFamily: "Gurmukhi"

    // Colors
    readonly property color geminiBaseColor: "#001a33"
    readonly property color geminiSecondColor: "#003566"
    readonly property color geminiThirdColor: "#004f99"

    readonly property color highlightColor: "#339cff"

    readonly property color geminiTextBaseColor: "white"
    readonly property color geminiTextStyleBaseColor: "black"

    readonly property color successColor: "#009933"

    readonly property color secondTextItemBackgroundColor: "#ff6600"

    readonly property color blank: "transparent"
    readonly property color transparentBackgroundShadow: "#99000000"

    readonly property color unfinishedColor: "#a3a3c2"

    // Border
    readonly property int borderWidth: 1
    readonly property int borderBoldWidth: 2

    // Opacity
    readonly property real opacityVisible: 1
    readonly property real opacityDisabledVisible: 0.4
    readonly property real opacityHidden: 0

    // Visibility
    readonly property int visible: 1
    readonly property int hidden: 0

    // None
    readonly property int none: 0

    // Capacity
    readonly property int empty: 0

    // Animations
    readonly property int quickAnimation: 200
    readonly property int animation: 500
    readonly property int slowAnimation: 1000

    // Components
    readonly property int playlistNewImplicitWidth: 250

    readonly property int toolTipAnimation: 50

    readonly property int separatorWidth: 2

    readonly property int wallpapersViewCellWidth: 100
    readonly property int wallpapersViewCellHeight: 100

    readonly property int audioProgressBarImplicitWidth: 250
    readonly property int audioProgressBarImplicitHeight: 250

    readonly property int gBaseDialogImplicitWidth: 400
    readonly property int gBaseDialogImplicitHeight: 50

    readonly property int controlImplicitWidth: 200
    readonly property int controlImplicitHeight: 40

    readonly property int wallpaperToolButtonIntervalFontSize: 10
}
