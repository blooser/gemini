import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQml 2.14

import com.gemini.styles 0.1
import com.gemini.helper 0.1
import com.gemini.enums 0.1
import com.gemini.tools 0.1

import "../components" as Components
import "../components/audio" as Audio
import "../items" as Items

GWallpaperPage {
    id: root

    Binding {
        target: sessionController
        property: "cleanScreen"
        value: (playlistModel.size === GeminiStyles.empty)
        restoreMode: Binding.RestoreBindingOrValue
    }

    Binding {
        target: sessionController
        property: "pending"
        value: (pendingModel.size > GeminiStyles.empty)
        when: !sessionController.unfinishedPeding
        restoreMode: Binding.RestoreBindingOrValue
    }

    Player {
        id: player
        volume: sessionController.audioVolume
        source: sessionController.currentSong.url
        muted: sessionController.audioMuted
        onMediaEnd: sessionController.nextSong()
    }

    Playlist {
        id: geminiPlaylist

        playlists: playlistModel
        songs: songsInRelations

        onPlaylistChanged: sessionController.currentPlaylist = playlist
        onCurrentSongChanged: sessionController.currentSong = currentSong
        onPlaybackChanged: sessionController.playback = playback

        Component.onCompleted: {
            songsInRelations.currentPlaylist = sessionController.currentPlaylist
            // Playlist properties
            playback = sessionController.playback
            selectPlaylist(sessionController.currentPlaylist.id, Playlist.SelectById)
            selectSong(sessionController.currentSong.id, Playlist.SelectById)
        }
    }

    Connections {
        target: sessionController

        function onNextSong()  { geminiPlaylist.next() }
        function onPreviousSong() { geminiPlaylist.previous() }
        function onSwitchPlayback() { geminiPlaylist.switchPlayback() }
        function onSelectPlaylist() { geminiPlaylist.selectPlaylist(id, selection) }
        function onSelectSong() { geminiPlaylist.selectSong(id, selection) }

        function onTogglePlayer() { player.toggle() }

        function onPendingChanged(pending) {
            if (pending) {
                objectController.openDialog(Enums.Dialog.PendingDialog, {}, null)
            }
        }
    }

    Components.Dashboard {
        id: dashboard

        audioControlEnabled: player.hasAudio

        anchors {
            fill: parent
            margins: GeminiStyles.nMargin
        }

        song: geminiPlaylist.currentSong
        playing: (player.status === Player.Playing)
    }

    Audio.AudioProgressbar {
        anchors.centerIn: parent

        visible: !sessionController.cleanScreen
        enabled: player.hasAudio

        from: 0
        to: player.duration
        value: player.time

        backgroundColor: GeminiStyles.geminiThirdColor
        progressbarColor: GeminiStyles.highlightColor

        onChangeValue: player.time = newValue
    }
}

