import QtQuick
import QtQuick.Controls.Basic

Window {
    width: 640
    height: 640
    visible: true
    title: qsTr("Hello World")

    // Rectangle
    // {
    //     x:0
    //     y:0
    //     width:300
    //     height:400
    //     border.color: "black"
    //     border.width: 2

    //     Column
    //     {
    //         id:col
    //         anchors.fill: parent
    //         spacing: 20
    //         leftPadding: 30 //相对于Column的内边距，又Column充满Rectangle，所以相对于Rectangle的内边距

    //         property alias repeater:repe
    //         Repeater
    //         {
    //             id:repe
    //             model:ListModel
    //             {
    //                 ListElement{btnName:0}
    //                 ListElement{btnName:1}
    //                 ListElement{btnName:2}
    //             }

    //             Button
    //             {
    //                 y:index*50
    //                 width:200
    //                 height:50
    //                 text: "button "+btnName
    //             }
    //         }

    //         //Column中元素首次创建时的动画效果
    //         populate: Transition
    //         {
    //             PropertyAnimation
    //             {
    //                 properties: "x,y"
    //                 from:200
    //                 duration: 1000
    //                 easing.type: Easing.OutBounce   //播放结束前弹簧跳动效果
    //             }
    //         }

    //         //向Column中添加元素时的动画效果
    //         add:Transition
    //         {
    //             NumberAnimation
    //             {
    //                 properties: "x,y"
    //                 easing.type: Easing.OutBounce   //弹跳
    //             }
    //         }

    //         //Column中元素移动时的动画效果
    //         move:Transition
    //         {
    //             NumberAnimation
    //             {
    //                 properties: "x,y"
    //                 easing.type: Easing.OutBounce   //弹跳
    //             }
    //         }
    //     }

    //     Button
    //     {
    //         id:btnAdd
    //         text: "add"
    //         anchors.left:parent.left
    //         anchors.leftMargin: 10
    //         anchors.bottom: parent.bottom
    //         anchors.bottomMargin: 20
    //         width:100
    //         height:50
    //         onClicked:
    //         {
    //             col.repeater.model.insert(0, {btnName:col.repeater.model.count})//在index=0处插入
    //         }
    //     }

    //     Button
    //     {
    //         id:btnRemove
    //         text: "remove"
    //         anchors.left:parent.left
    //         anchors.leftMargin: 10
    //         anchors.bottom: btnAdd.top
    //         anchors.bottomMargin: 20
    //         width:100
    //         height:50
    //         onClicked:
    //         {
    //             col.repeater.model.remove(0)//移除index=0处1个
    //         }
    //     }
    // }


    property real _x:100
    property real _y:100
    HeartRound
    {
        id:hr1
        r:50
        x:_x
        y:_y
        word:"I"
    }

    HeartRound
    {
        id:hr2
        r:50
        x:_x+1.4142*r
        y:_y
        word:"Love"
    }

    HeartSquare
    {
        id:hs
        r:50
        x:_x+0.7071*r
        y:_y+0.7071*r
        word:"You"
    }

    Button
    {
        id:change
        width:100
        height:50
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        text:"click me!!"

        onPressed:
        {
            hr1.changeToSt2()
            hr2.changeToSt2()
            hs.changeToSt2()
        }

        onReleased:
        {
            hr1.changeToSt1()
            hr2.changeToSt1()
            hs.changeToSt1()
        }
    }

}
