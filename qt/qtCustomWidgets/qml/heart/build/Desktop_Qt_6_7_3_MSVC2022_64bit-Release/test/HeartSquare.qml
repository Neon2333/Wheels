import QtQuick

Rectangle
{
    id:rect
    property string word:"Love"
    property real r: 25
    width:r*2
    height:r*2
    color:"transparent"
    transformOrigin:Item.Center

    Text
    {
        id:label
        anchors.fill: parent
        anchors.centerIn: parent.Center
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        text:word
        color:"black"
        font.pixelSize: 10
        font.bold: true
        font.italic: true
        opacity:1
    }

    states:
    [
        State
        {
            name:"st1"
            PropertyChanges {target:label;opacity:1;}
            PropertyChanges {target:rect;color:"transparent";rotation:0}
        },

        State
        {
            name:"st2"
            PropertyChanges {target:label;opacity:0;}
            PropertyChanges {target:rect;color:"red";rotation:45}
        }
    ]

    transitions:
    [
        Transition
        {
            from:"st1"
            to:"st2"
            NumberAnimation{target:label;properties: "opacity";duration:300}
            PropertyAnimation{target:rect;properties:"color,rotation";duration:300}
        },

        Transition
        {
            from:"st2"
            to:"st1"
            NumberAnimation{target:label;properties: "opacity";duration:300}
            PropertyAnimation{target:rect;properties:"color,rotation";duration:300}
        }
    ]

    function changeToSt2()
    {
        rect.state="st2"
    }

    function changeToSt1()
    {
        rect.state="st1"
    }

    MouseArea
    {
        anchors.fill: parent
        // onPressed:
        // {
        //     rect.state="st2"
        // }

        // onReleased:
        // {
        //     rect.state="st1"
        // }

        onClicked:
        {
            rect.state="st2"
        }
    }
}
