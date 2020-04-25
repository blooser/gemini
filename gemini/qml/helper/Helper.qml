pragma Singleton

import com.gemini.enums 0.1

import QtQuick 2.14

QtObject {
    function empty(item) {
        return (item.length === 0)
    }

    function toList(items) {
        var stringList = []
        for (const item of items) {
            stringList.push(item)
        }

        return stringList
    }

    function createRelation(playlist, songs) {
        var relation = []

        for (const song of songs) {
            relation.push({"playlist": playlist, "song": song})
        }

        return relation
    }

    function selectNextIndex(index, count) {
        return index - 1 >= 0 ? index - 1
                              : index + 1 < count ? index + 1
                                                  : -1
    }

    function extraHumanTimeFormat(ms) {
        if (ms < 60000) {
            return "s 's'"
        } else if (ms % 60000 === 0) {
            return "m 'm'"
        } else {
            return "m 'm' s 's'"
        }
    }

    function detectExtraHumanTimeFormat(string) {
        let match =  /^([0-9]?[0-9] m)? ?([0-9]?[0-9] s)?/.exec(string)

        if (match.length === 0) {
            return ""
        }

        match = match[0]

        if (match.includes("s") && !match.includes("m")) {
            return "s 's'"
        } else if (match.includes("m") && match.includes("s")) {
            return "m 'm' s 's'"
        } else if (match.includes("m") && !match.includes("s")) {
            return "m 'm'"
        }

        return ""
    }
}
