import QtQuick 2.0
import QtTest 1.0

import com.gemini.tools 0.1

Item {
    CircleProgressBar {
        id: circleProgressBar

        from: 0
        value: 50
        to: 100

        backgroundColor: "#342123"
        progressbarColor: "#563231"
    }

    TestCase {
        name: "CircleProgressBarQuickTest"

        function test_fromInitializationV() {
            compare(circleProgressBar.from, 0)
        }

        function test_valueInitialization() {
            compare(circleProgressBar.value, 50)

        }

        function test_toInitialization() {
            compare(circleProgressBar.to, 100)
        }

        function test_backgroundColorInitialization() {
            compare(circleProgressBar.backgroundColor, "#342123")

        }

        function test_progressbarColorInitialization() {
            compare(circleProgressBar.progressbarColor, "#563231")
        }
    }
}



