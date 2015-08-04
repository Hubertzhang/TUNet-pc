import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

ListItem.Subtitled {
    visible: true
    text: (number == 0 ? connectionName0 : number == 1 ? connectionName1 : connectionName2) != "" ?
           number == 0 ? connectionName0 : number == 1 ? connectionName1 : connectionName2 : "未知设备"
    subText: number == 0 ? connectionTraffic0 : number == 1 ? connectionTraffic1 : connectionTraffic2
    secondaryItem: Button {
        text: "断开"
        elevation: 1
        width: 32
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        onClicked: connection.logoutRequest(number);
    }
    action: Icon {
        anchors.centerIn: parent
        name: "awesome/laptop"
        size: Units.dp(28)
    }

    Dialog {
        id: info
        title: "Detailed Information"
        height: 400
        TextField {
            id: deviceName
            placeholderText: "(设备名称)"
            text: number == 0 ? connectionName0 : number == 1 ? connectionName1 : connectionName2
            height: 50
            width: parent.width
        }
        ListItem.Subtitled {
            height: 40
            margins: Units.dp(2)
            text: "上线时间"
            subText: number == 0 ? connectionTime0 : number == 1 ? connectionTime1 : connectionTime2
        }
        ListItem.Subtitled {
            height: 40
            margins: Units.dp(2)
            text: "IP地址"
            subText: number == 0 ? connectionIp0 : number == 1 ? connectionIp1 : connectionIp2
        }
        ListItem.Subtitled {
            id: macAdress
            height: 40
            margins: Units.dp(2)
            text: "MAC地址"
            subText: number == 0 ? connectionAddress0 : number == 1 ? connectionAddress1 : connectionAddress2
        }
        ListItem.Subtitled {
            height: 40
            margins: Units.dp(2)
            text: "流量统计"
            subText: number == 0 ? connectionTraffic0 : number == 1 ? connectionTraffic1 : connectionTraffic2
        }
        onAccepted: connection.okClicked(number,macAdress.subText,deviceName.text);
    }

    onClicked: info.show()
}
