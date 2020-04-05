import QtQuick 2.0
import QtTest 1.0

import com.gemini.tools 0.1

TestCase {
    name: "PickerTest"

    ListModel {
        id: testModel

        ListElement { name: "test1" }
        ListElement { name: "test2" }
        ListElement { name: "test3" }
        ListElement { name: "test4" }
        ListElement { name: "test5" }
    }

    SignalSpy {
        id: pickedSignalSpy
        target: picker
        signalName: "picked"
    }

    Picker {
        id: picker

        interval: 15000
        roleName: "name"
        model: testModel
    }

    function initTestCase() {
        compare(picker.interval, 15000)
        compare(picker.roleName, "name")
        compare(picker.model, testModel)

        // First pick on initialize
        compare(typeof picker.data, "string")
        verify(picker.data.length)
        compare(pickedSignalSpy.count, 1)
    }

    ListModel {
        id: changingModel

        function extend() {
            append({"name": "test"})
        }

        function reduce() {
            remove(0)
        }
    }

    SignalSpy {
        id: modelSizeChangedSignalSpy
        target: picker
        signalName: "modelSizeChanged"
    }

    function test_pickerUpdatesModelSizePropertyWhenTargetModelSizeChanged() {
        modelSizeChangedSignalSpy.clear()

        picker.model = changingModel
        compare(picker.modelSize, 0)

        changingModel.extend()
        compare(picker.modelSize, 1)

        changingModel.extend()
        compare(picker.modelSize, 2)

        changingModel.reduce()
        compare(picker.modelSize, 1)

        changingModel.reduce()
        compare(picker.modelSize, 0)

        compare(modelSizeChangedSignalSpy.count, 5)
    }
}
