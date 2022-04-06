import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle{
    id:root
    color: "#B0AFAFAF"
    property alias newGameButton: newGameButton
    Rectangle{
        color: "lightgray"
        width: parent.width < parent.height ? parent.width*0.75 : parent.height*0.75
        height: width/2
        anchors.centerIn: parent
        Text{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -parent.height*0.25
            font.pixelSize: parent.height*0.2
            text: "Puzzle solved!"
        }
        Button{
            id:newGameButton
            height: parent.height*0.25
            width: height*2.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.2
            text: "New Game"
        }
    }
}
