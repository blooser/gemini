import QtQuick 2.12
import QtTest 1.12

import com.gemini.tools 0.1

TestCase {
    name: "PlaylistQuickTest"

    Playlist {
        id: playlist
    }

    SignalSpy {
        id: playlistSignalSpy
        target: playlist
        signalName: "playlistChanged"
    }

    SignalSpy {
        id: currentSongSignalSpy
        target: playlist
        signalName: "currentSongChanged"
    }

    function initTestCase() {
        playlist.playlists = playlistModel

        verify(playlist.playlists)
        compare(playlist.playlists.rowCount(), 2)

        playlist.selectPlaylist(1)
        var currentPlaylist = playlist.playlist
        compare(currentPlaylist.id, 1)
        compare(currentPlaylist.name, "playlist1")
        compare(playlistSignalSpy.count, 1)
    }

    function init() {
        playlist.songs = songModel

        verify(playlist.songs)
        compare(playlist.songs.rowCount(), 2)

        currentSongSignalSpy.clear()
    }

    function test_sequental() {
        playlist.playback = Playlist.Sequental

        playlist.next()
        compare(playlist.currentIndex, 0)
        playlist.next()
        compare(playlist.currentIndex, 1)

        playlist.previous()
        compare(playlist.currentIndex, 0)
        playlist.previous()
        compare(playlist.currentIndex, 0)

        compare(currentSongSignalSpy.count, 4)
    }

    function test_loop() {
        playlist.playback = Playlist.Loop

        playlist.next()
        compare(playlist.currentIndex, 0)
        playlist.next()
        compare(playlist.currentIndex, 1)
        playlist.next()
        compare(playlist.currentIndex, 0)

        playlist.previous()
        compare(playlist.currentIndex, 1)
        playlist.previous()
        compare(playlist.currentIndex, 0)
        playlist.previous()
        compare(playlist.currentIndex, 1)

        compare(currentSongSignalSpy.count, 6)
    }

    function test_switchPlayback() {
        playlist.playback = Playlist.Sequental

        playlist.switchPlayback()
        compare(playlist.playback, Playlist.Loop)

        playlist.switchPlayback()
        compare(playlist.playback, Playlist.Random)

        playlist.switchPlayback()
        compare(playlist.playback, Playlist.Sequental)
    }

    function test_selectSong() {
        playlist.selectSong(2, Playlist.SelectById)
        compare(currentSongSignalSpy.count, 1)

        var currentSong = playlist.currentSong
        compare(currentSong.id, 2)
        compare(currentSong.url, "/foo/path2")
    }

    ListModel {
        id: playlists

        Component.onCompleted: {
            const items = [
                {"id": 0, "name": "Playlist1"},
                {"id": 1, "name": "Playlist1"},
            ]

            for (const item of items) {
                append(item)
            }
        }
    }

    Playlist {
        id: playlist1
    }

    SignalSpy {
        id: playlistChangedSignalSpy1
        target: playlist1
        signalName: "playlistChanged"
    }

    SignalSpy {
        id: currentSongChangedSignalSpy1
        target: playlist1
        signalName: "currentSongChanged"
    }

    function test_playlistErasedItselfWhenPlaylistModelIsEmpty() {
        playlist1.songs = songModel
        playlist1.playlists = playlists

        playlist1.selectPlaylist(0, Playlist.SelectByIndex)
        playlist1.selectSong(0, Playlist.SelectByIndex)
        verify(playlist1.playlist.id !== -1)
        verify(playlist1.currentSong.id !== -1)

        verify(playlist1.songs.rowCount() > 0)
        compare(playlist1.playlists.rowCount(), 2)

        playlistChangedSignalSpy1.clear()
        currentSongChangedSignalSpy1.clear()

        playlists.clear()
        compare(playlistChangedSignalSpy1.count, 1)
        compare(currentSongChangedSignalSpy1.count, 1)

        verify(playlist1.playlist.id === -1)
        verify(playlist1.currentSong.id === -1)
    }
}
