import QtQuick 2.15
//import "GameLogic.js" as Logic
import Plugins.ModelPlugin 1.0
GridView{
    id: root
    readonly property int size: 4
    signal solved()
    model: MyModel{
        id:gridModel
    }
    cellWidth: width/size
    cellHeight: height/size
    interactive: false
//    Transition {
//        id: transition
//        NumberAnimation { properties: "scale"; from: 0; to: 1; duration: 2000; easing.type: Easing.OutBounce }
//    }
//    add: transition
//    move:  transition
//    displaced: transition


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

