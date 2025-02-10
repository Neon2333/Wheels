import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Window
import Qt5Compat.GraphicalEffects

Window {
    width: 1280
    height: 1080
    visible: true
    title: qsTr("Hello World")

    //hover时图片边缘阴影
    DropShadow
    {
        id:showdow
        visible:false
        anchors.fill: img
        source:img
        horizontalOffset: 10
        verticalOffset: 15
        radius:15.0
        samples:17
        color:"#80000000"
    }

    Image
    {
        id:img
        source:"file:/G:/Pictures/wallpaper/v2-11cb35bacf765bfe8a3e3dc40ba5b131_r.jpg"
        smooth: true
        width:800
        height:600

        Rectangle
        {
            id:txt1
            width:img.width/4
            height:img.height
            anchors.right: img.right
            anchors.top:img.top
            // anchors.rightMargin: 10
            // border.color: "royalblue"
            border.width: 0
            color:Qt.rgba(0,0,0,0.5)

            state:"stExisted"

            Column
            {
                id:col
                spacing: 10
                anchors.fill:parent
                opacity:1.0
                anchors.horizontalCenter: parent.horizontalCenter

                Text
                {
                    text:"This is Picture"
                    color:"white"
                    font.pixelSize: 24
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text
                {
                    text:"info"
                    color:"white"
                    font.pixelSize: 12
                    font.bold: false
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        states:
        [
            State
            {
                name: "stEnter"
                PropertyChanges {target: txt1;  width:img.width/4}
                PropertyChanges {target: col;  opacity:1.0;}
            },
            State
            {
                name: "stExisted"
                PropertyChanges {target: txt1;  width:0}
                PropertyChanges {target: col;  opacity:0.0;}
            }
        ]

        transitions:
        [
            Transition
            {
                from: "stEnter"
                to: "stExisted"
                PropertyAnimation{target:txt1;properties: "width"; duration:300}
                PropertyAnimation{target:col;properties: "opacity"; duration:300}
            },
            Transition
            {
                from: "stExisted"
                to: "stEnter"
                PropertyAnimation{target:txt1;properties: "width"; duration:300}
                PropertyAnimation{target:col;properties: "opacity"; duration:300}
            }
        ]

        MouseArea
        {
            id:ma
            anchors.fill: img
            hoverEnabled: true
            onContainsMouseChanged:
            {
                if(containsMouse)
                {
                    txt1.anchors.right=img.right
                    txt1.anchors.top=img.top
                    // col.anchors.horizontalCenter=txt1.horizontalCenter
                    img.state="stEnter"
                }
                else
                {
                    // col.anchors.horizontalCenter=undefined
                    img.state="stExisted"
                }
            }
        }
    }
}
