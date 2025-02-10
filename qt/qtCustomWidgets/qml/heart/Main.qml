import QtQuick
import QtQuick.Controls.Basic

Window {
    width: 640
    height: 640
    visible: true
    title: qsTr("Hello World")

    property real _x:100
    property real _y:100
    property real _r:50
    HeartRound
    {
        id:hr1
        r:_r
        x:_x
        y:_y
        word:"I"
    }

    HeartRound
    {
        id:hr2
        r:_r
        x:_x+1.4142*r
        y:_y
        word:"Love"
    }

    HeartSquare
    {
        id:hs
        r:_r
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
