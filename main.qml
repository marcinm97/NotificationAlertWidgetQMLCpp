import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Rectangle { //background
        anchors.fill: parent
        color: "#292B38"
    }

    AlertsWidget{
        width: parent.width*0.97
        height: parent.height*0.6
        anchors.centerIn: parent
    }
}
