import QtQuick
import QtQuick.Controls.Basic


Item
{
  width: 200
  height: 200

  Component
  {
    id: rect
    Rectangle
    {
      color: "red"
      anchors.bottom:parent.bottom	//指定item位置
      anchors.bottomMargin:10
     }
  }

  Loader
  {
    anchors.fill: parent
    //width: 100	//会覆盖item设置的200，200
    //height: 100
    sourceComponent: rect	//也可以是通过属性，传入外部的组件
  }
}
