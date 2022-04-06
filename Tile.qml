import QtQuick 2.15
Item{
    id:root
    property bool isEmpty: false
    property string text: ""
    signal clicked()
    Rectangle{
        width: parent.width*0.95
        height: parent.height*0.95
        anchors.centerIn: parent
        visible: !isEmpty
        color: "cyan"
        radius: height*0.2
        border.width: height*0.01
        border.color: "lightgray"
        clip:true
        Text{
            anchors.centerIn: parent
            text: root.text
        }
        MouseArea{
            anchors.fill: parent
            onClicked: root.clicked()
        }
    }
}
