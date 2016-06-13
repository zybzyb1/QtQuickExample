import QtQuick 2.0

Rectangle {
    id:root
    property int icount: 3
    width: 180;
    height: 200

    //以下为QML中delegate的写法，里面可以直接使用C++Model中的字段来读取值
    Component {
        id: contactDelegate
        Rectangle {
            id:rootItem
            width: root.width;
            height: 40
            color:ma.containsMouse?"#01B6E1":"transparent" //只要包含鼠标事件就改变颜色 当然可以做其他的处理
            MouseArea{
                id:ma
                anchors.fill: parent
                hoverEnabled: true
            }
            Row {
                spacing:10
                anchors.fill: parent
                Text {
                    width: root.width/5
                    height: parent.height
                    text: '<b>测试</b>: ' + dName//此处为C++的Model中的 name字段
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                Image{
                    id:icons
                    source: dIcon//此处为C++model的icon字段
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    width: root.width*4/5-icons.sourceSize.width-20
                    height: parent.height
                    text: '描述信息: ' + dDesc//此处为C++model的desc字段
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
            }
        }
    }

    //以下是ListView的简洁写法 当然可以加入各种动画
    ListView {
        anchors.fill: parent
        model: driverModel
        delegate: contactDelegate
        focus: true
    }
    //以下为测试代码 模拟测试数据

    Timer {
        interval: 2000; running: true; repeat: true
        onTriggered: {
            var ii = 1174391+driverModel.rowCount();
            var url = "http://download.easyicon.net/png/"+ii+"/32/";
            var lst = ["Item:"+driverModel.rowCount(),url,"测试C++Model在QML中的使用ccccccccccccccccccccc"];
            //以下为C++的Model可以使用增删查改功能
            driverModel.addSomeItem(lst);
        }
    }
}

