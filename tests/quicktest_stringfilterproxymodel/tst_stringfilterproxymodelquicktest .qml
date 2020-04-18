import QtQuick 2.14
import QtTest 1.12

import com.gemini.tools 0.1

TestCase {
    name: "StringFilterProxyModelTest"
    
    ListModel {
        id: testModel
        
        ListElement { title: "test1" }
        ListElement { title: "test2" }
        ListElement { title: "test3" }
        ListElement { title: "sky1" }
        ListElement { title: "space1" }
    }
    
    StringFilterProxyModel {
        id: stringFilterProxyModel
        sourceModel: testModel
    }
    
    function test_stringFilterProxyModelFiltersData() {
        stringFilterProxyModel.string = "test"
        compare(stringFilterProxyModel.rowCount(), 3)

        stringFilterProxyModel.string = "sky"
        compare(stringFilterProxyModel.rowCount(), 1)

        stringFilterProxyModel.string = "1"
        compare(stringFilterProxyModel.rowCount(), 3)
    }
}
