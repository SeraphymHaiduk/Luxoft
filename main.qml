import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
//import "GameLogic.js" as Logic
import Plugins.ModelPlugin 1.0
Window{
    id: root
    width: 400
    height: 680
    visible:true
    Item{
        id:frame
        width: parent.width*1.2 < parent.height ? parent.width : parent.height/1.2
        height: width*1.2
        anchors.centerIn:parent
        GameBoard{
            id:gameBoard
            width:parent.width
            height: width
            anchors{
                left:parent.left
                right: parent.right
                top: parent.top
            }
            onSolved: {
                menuLoader.sourceComponent = winMsgComponent
            }
        }
        Button{
            id: mixButton
            anchors.top: gameBoard.bottom
            anchors.bottom: parent.bottom
            anchors.margins: (frame.height-gameBoard.height)*0.25
            anchors.horizontalCenter: parent.horizontalCenter
            width: gameBoard.width*0.3
            text: "mix"
            onClicked: Logic.mix(gameBoard.model,gameBoard.size)
        }
    }

    Loader{
        id:menuLoader
        anchors.fill: parent
        sourceComponent: undefined
    }
    Component{
        id: winMsgComponent
        WinMessage{
            Component.onCompleted: {
                newGameButton.clicked.connect(()=>{
                menuLoader.sourceComponent = undefined
                Logic.mix(gameBoard.model,gameBoard.size)
              })
            }
        }
    }

}

