import QtQuick 2.15
import "GameLogic.js" as Logic
GridView{
    id: root
    readonly property int size: 4
    signal solved()
    model: GridModel{
        id:gridModel
    }
    cellWidth: width/size
    cellHeight: height/size
    interactive: false
    move: Transition {
        NumberAnimation { properties: "x,y"; duration: 800; easing.type: Easing.OutBounce }
    }
    delegate: Tile{
        id:tileDelegate
        isEmpty: value === 16
        width: GridView.view.cellWidth
        height: GridView.view.cellHeight
        text: value
        onClicked:{
            Logic.moveTile(root.model,index,root.size)
            if(Logic.isSolved(root.model,root.size)){
                root.solved()
            }
        }
    }
}

