import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4

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
        id: alertsWidget
        width: parent.width*0.97
        height: parent.height*0.6
        anchors.centerIn: parent
    }
    Rectangle{
    id: inputBackground
    color: "white"
    height: parent.height*0.1
    width: parent.width*0.45
    anchors {
        left: parent.left
        bottom: parent.bottom
        leftMargin: height
        bottomMargin: height*0.5
    }

    TextEdit {
        id: textEdit
        anchors.centerIn: parent
        property string placeHolder: "Add your error or info here..."
        width: parent.width*0.8
        height: parent.height*0.3
        font.pointSize: parent.height*0.2

    Text{
        text: textEdit.placeHolder
        opacity: 0.7
        visible: !textEdit.text && !textEdit.activeFocus
        font.pixelSize: textEdit.font.pixelSize

    }
    }
    }
    ComboBox {
        id:comboBox
        model: ["information", "warning"]
        anchors.verticalCenter: button.verticalCenter
        anchors.right: button.left
        anchors.rightMargin: parent.width*0.02
    }

    Button {
        id: button
        text: "Add"
        height: inputBackground.height*1.2
        width: inputBackground.width*0.2
        anchors {
            verticalCenter: inputBackground.verticalCenter
            right: parent.right
            rightMargin: parent.width*0.12
        }
        onClicked: {
            //invoke add function here
            textEdit.text = ""
        }
    }
}
