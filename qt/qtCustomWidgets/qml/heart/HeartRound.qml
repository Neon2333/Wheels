import QtQuick
import QtQuick.Controls.Basic

Rectangle
{
    id:rect
    property string word:"Love"
    property real r: 25
    width:r
    height:r
    radius:r*0.5
    color:"transparent"
    transformOrigin:Item.Center

    Text
    {
        id:label
        anchors.fill: parent
        anchors.centerIn: parent.Center
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text:word
        color:"black"
        font.pixelSize: 15
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
            PropertyChanges {target:rect;color:"transparent";width:r;height:r;radius:r*0.5;}
        },

        State
        {
            name:"st2"
            PropertyChanges {target:label;opacity:0;}
            PropertyChanges {target:rect;color:"red";width:r*2;height:r*2;radius:r;}
        }
    ]

    transitions:
    [
        Transition
        {
            from:"st1"
            to:"st2"
            NumberAnimation{target:label;properties: "opacity";duration:300}
            PropertyAnimation{target:rect;properties:"color,width,height,radius";duration:300}
            // ScaleAnimator{target:_rect;from:0.5;to:1;duration:500;running: true}
        },

        Transition
        {
            from:"st2"
            to:"st1"
            NumberAnimation{target:label;properties: "opacity";duration:300}
            PropertyAnimation{target:rect;properties:"color,width,height,radius";duration:300}
            // ScaleAnimator{target:_rect;from:1;to:0.5;duration:500;running: true}
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






