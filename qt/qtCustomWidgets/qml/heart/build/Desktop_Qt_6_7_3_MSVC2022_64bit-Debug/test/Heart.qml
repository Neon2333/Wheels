import QtQuick
import QtQuick.Controls.Basic

// Rectangle
// {
//     id:rect
//     width:50
//     height:50
//     radius:25
//     color:"red"
//     transformOrigin:Item.Center

//     Text
//     {
//         id:label
//         anchors.fill: parent
//         anchors.centerIn: parent.Center
//         horizontalAlignment: Text.AlignHCenter
//         verticalAlignment: Text.AlignVCenter
//         text:"Love"
//         color:"black"
//         font.pixelSize: 10
//         font.bold: true
//         font.italic: true
//         opacity:1
//     }

//     states:
//     [
//         State
//         {
//             name:"st1"
//             PropertyChanges {target:label;opacity:1;}
//             PropertyChanges {target:rect;color:"red";width:50;height:50;radius:25;}
//         },

//         State
//         {
//             name:"st2"
//             PropertyChanges {target:label;opacity:0;}
//             PropertyChanges {target:rect;color:"red";width:100;height:100;radius:50;}
//         }
//     ]

//     transitions:
//     [
//         Transition
//         {
//             from:"st1"
//             to:"st2"
//             NumberAnimation{target:label;properties: "opacity";duration:300}
//             PropertyAnimation{target:rect;properties:"color,width,height,radius";duration:300}
//             // ScaleAnimator{target:_rect;from:0.5;to:1;duration:500;running: true}
//         },

//         Transition
//         {
//             from:"st2"
//             to:"st1"
//             NumberAnimation{target:label;properties: "opacity";duration:300}
//             PropertyAnimation{target:rect;properties:"color,width,height,radius";duration:300}
//             // ScaleAnimator{target:_rect;from:1;to:0.5;duration:500;running: true}
//         }
//     ]

//     MouseArea
//     {
//         anchors.fill: parent
//         onPressed:
//         {
//             rect.state="st2"
//         }

//         onReleased:
//         {
//             rect.state="st1"
//         }
//     }
// }


Item
{
    Rectangle
    {
        property real r:0
        id:rect
        width:50
        height:50
        radius:r
        color:"red"
        transformOrigin:Item.Center

        Text
        {
            id:label
            anchors.fill: parent
            anchors.centerIn: parent.Center
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text:"Love"
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
                PropertyChanges {target:rect;color:"red";width:50;height:50;radius:25;}
            },

            State
            {
                name:"st2"
                PropertyChanges {target:label;opacity:0;}
                PropertyChanges {target:rect;color:"red";width:100;height:100;radius:50;}
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

        MouseArea
        {
            anchors.fill: parent
            onPressed:
            {
                rect.state="st2"
            }

            onReleased:
            {
                rect.state="st1"
            }
        }
    }


}



