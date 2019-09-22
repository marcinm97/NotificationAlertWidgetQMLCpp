import QtQuick 2.0
import QtQuick.Controls 2.4
import "listViewFun.js" as ListFun

Item {
    id: root
    property color topBarColor: "#313646"
    property color textColor: "#999AA3"
    property color backgroundColor: "#424D5C"
    property color delegateBodyColor: "#363b4d"
    property color delegateBorderColor: "#F2B81E"
    property color delegateTextColor: "white"
    property bool clearAllButtonVisiblity: true

    FontLoader{
        id: standardFont
        source: "qrc:/assets/agency_fb.ttf"
    }

    Rectangle {
        id: alertsBackground
        anchors.fill:parent
        color: backgroundColor
        radius: height*0.02


        //================= TOPBAR
        Rectangle { //tob bar
            id: alertsTopBar
            height: root.height*0.3
            width: parent.width
            radius: parent.height*0.02
            color: topBarColor
            anchors {
                top:parent.top
                horizontalCenter: parent.horizontalCenter

            }
            Image { //change to trashbin Icon
                id: clearListViewButton
                visible: clearAllButtonVisiblity
                source: "qrc:/assets/CLEARALLALERTS.svg"
                height: parent.height*0.7
                smooth: true
                width: height
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: alertsPropertiesSquares.left
                    rightMargin: width*0.5
                }

                // TOOLS TIP - START

                  ToolTip {
                      id: binTip
                      text: "REMOVE ALL MESSAGES"
                      visible: binMouseArea.containsMouse

                      contentItem: Text {
                          text: binTip.text
                          font.bold: true
                          font.family: standardFont.name
                          color: "#F2B81E"
                      }

                      background: Rectangle {
                          border.color: "#F2B81E"
                          color: "#424D5C"
                          radius: 5
                      }
                  }

                // TOOLS TIP - END


                MouseArea {
                    id: binMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        errorModel.clear()
                    }
                }
            }

            Image { //properties squares
                id: alertsPropertiesSquares
                height: parent.height*0.5
                width: parent.width*0.012
                opacity: 0.75
                source: "qrc:/assets/PROPERTIES SQUARES.png"
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    rightMargin: 0.03*parent.width
                }
            }
            Image { //alert icon
                id:alertsIcon
                height: parent.height*0.36
                width: height
                source: "qrc:/assets/NotificationIcon.png"
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 0.03*parent.width
                }
            }
                Text {
                    font.pointSize: 0.8*alertsIcon.height.toFixed(0)
                    font.family: standardFont.name
                    text: ("Alerts").toUpperCase()
                    color: textColor
                    font.bold: true
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: alertsIcon.right
                        leftMargin: alertsIcon.width*0.3
                    }

                }

            }
        //================= ListView
        ListView{
             width: alertsBackground.width
             model: errorModel

             add: Transition {
                       NumberAnimation { properties: "y"; from: alertsBackground.height; duration: 300 }
                   }
             remove: Transition {
                 NumberAnimation { properties: "opacity"; to: 0; duration: 300 }
             }
             move: Transition{NumberAnimation { properties: "y"; duration: 300}}

             displaced: Transition {
                 SequentialAnimation{
                 PauseAnimation{duration: 200}
                 NumberAnimation { properties: "y"; duration: 300 }
                 }
             }
             //-----------------------anim
             clip: true
             spacing: alertsBackground.height*0.02
             ScrollBar.vertical: ScrollBar {
             active: true
             anchors {
                 right: parent.right
                 verticalCenter: parent.verticalCenter
             }
             }
             delegate: delegate
             anchors {
             top: alertsTopBar.bottom
             topMargin: alertsBackground.height*0.02
             horizontalCenter: alertsBackground.horizontalCenter
             bottom: parent.bottom
             }

               }

        }
    Component{

    id: delegate


    Rectangle {
    color: delegateBodyColor
    width: alertsBackground.width
    height: alertsBackground.height*0.2
    radius: height*0.2
    border{
        color: delegateBorderColor
        width: height*0.02
    }
    Image {
        id: messageTypeIcon
        height: parent.height*0.6
        source: {
            if(type==0){
               source = "qrc:/assets/okIcon.png"
            }else if(type ==1){
                source = "qrc:/assets/exampleAlertIcon2.png"
            }
            else {source = "qrc:/assets/exampleAlertIcon.png"}
        }

        width: height
        anchors{
            left: parent.left
            leftMargin: height*0.3
            verticalCenter: parent.verticalCenter
        }
    }

    Text {
         anchors{
             left: messageTypeIcon.right
             leftMargin: messageTypeIcon.width*0.2
             verticalCenter: parent.verticalCenter
         }
         color: delegateTextColor
         font.pixelSize: messageTypeIcon.height
         font.family: standardFont.name
         text: msg
            }

    Image {
        anchors.right: parent.right
        anchors.rightMargin: width*0.5
        anchors.verticalCenter: parent.verticalCenter
        width: height
        visible: {
            if(!type){
                visible = false
            }
            else{ visible = true
            }
        }
        height: parent.height*0.7
        source: "qrc:/assets/CLEARONEALERT.svg"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                errorModel.remove(index)
            }
        }
    }
    }
    }
    ListModel {
        id: errorModel
        onCountChanged: {
            ListFun.checkList()
        }
        ListElement {
            type: 0
            msg: "No problem detected"
            selected: false
        }
}


}
