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

    function extraHumanTime(ms) {
        if (ms < 60000) {
            return "s 's'"
        } else if (ms % 60000 === 0) {
            return "m 'm'"
        } else {
            return "m 'm' s 's'"
        }
    }
}
