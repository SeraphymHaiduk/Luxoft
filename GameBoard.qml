import QtQuick 2.15
import Plugins.ModelPlugin 1.0
GridView{
    id: root
    signal solved()
    model: MyModel{
        id:gridModel
    }
    cellWidth: width/model.gridSize
    cellHeight: height/model.gridSize
    interactive: false
    move: Transition {
        NumberAnimation { properties: "x,y"; duration: 1000 ; easing.type: Easing.OutBounce }
    }
    delegate: Tile{
        id:tileDelegate
        isEmpty: value === 16
        width: GridView.view.cellWidth
        height: GridView.view.cellHeight
        text: value
        onClicked:{
            root.model.move(index)
            if(root.model.isSolved()){
                root.solved()
            }
        }
    }
}

