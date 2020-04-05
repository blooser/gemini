import QtQuick 2.14
import QtTest 1.12

import com.gemini.tools 0.1

TestCase {
    name: "SessionControllerTest"

    SignalSpy {
        id: currentPlaylistChangedSignalSpy
        target: sessionController
        signalName: "currentPlaylistChanged"
    }

    SignalSpy {
        id: currentSongChangeSignalSpy
        target: sessionController
        signalName: "currentSongChanged"
    }

    SignalSpy {
        id: currentWallpaperChangeSignalSpy
        target: sessionController
        signalName: "currentWallpaperChanged"
    }

    function test_pagesInitializeWithValidValues() {
        verify(sessionController.pages.length === 4)

        const expectedValues = [
            {
                "icon": "qrc:/icons/gate",
                "name": "Summary"
            },
            {
                "icon": "qrc:/icons/music",
                "name": "Music"
            },
            {
                "icon": "qrc:/icons/playlist",
                "name": "Playlists"
            },
            {
                "icon": "qrc:/icons/images",
                "name": "Wallpapers"
            },
        ]

        for (var i=0; i<sessionController.pages.length; ++i) {
            compare(sessionController.pages[i].icon, expectedValues[i].icon)
            compare(sessionController.pages[i].name, expectedValues[i].name)
        }
    }

    function test_setCleanScreenMode() {
        const expectedValue = true
        sessionController.cleanScreen = expectedValue
        compare(sessionController.cleanScreen, expectedValue)
    }

    function test_setAudioMutedPlay() {
        const expectedValue = true
        sessionController.audioMuted = expectedValue
        compare(sessionController.audioMuted, expectedValue)
    }

    function test_setPending() {
        const expectedValue = true
        sessionController.pending = expectedValue
        compare(sessionController.pending, expectedValue)
    }

    function test_setPlayback() {
        const expectedValue = Playlist.Random
        sessionController.playback = expectedValue
        compare(sessionController.playback, expectedValue)
    }

    function test_setPlaylist() {
        sessionController.currentPlaylist = playlist;

        compare(sessionController.currentPlaylist, playlist)
        compare(currentPlaylistChangedSignalSpy.count, 1)
        var currentPlaylist = currentPlaylistChangedSignalSpy.signalArguments[0][0]
        compare(currentPlaylist.id, playlist.id)
        compare(currentPlaylist.name, playlist.name)
    }

    function test_setAudioVolume() {
        const expectedValue = 75
        sessionController.audioVolume = expectedValue
        compare(sessionController.audioVolume, expectedValue)
    }

    function test_setCurrentSong() {
        sessionController.currentSong = song

        compare(sessionController.currentSong, song)

        compare(currentSongChangeSignalSpy.count, 1)
        var currentsong = currentSongChangeSignalSpy.signalArguments[0][0]
        compare(currentsong.id, song.id)
        compare(currentsong.url, song.url)
        compare(currentsong.playlist, playlist)
    }

    function test_setCurrentWallpaper() {
        const expectedValue = "file:///foo/bar/path1"
        sessionController.currentWallpaper = expectedValue
        compare(sessionController.currentWallpaper.toString(), expectedValue)
    }

    function test_setCurrentPageIndex() {
        const expectedValue = 2
        sessionController.currentPageIndex = expectedValue
        compare(sessionController.currentPageIndex, expectedValue)
    }
}
