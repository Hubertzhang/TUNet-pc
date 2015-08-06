import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

Component {
Item {
    View {
        id: accountInfo
        elevation: 1
        anchors {
            fill: parent
            margins: Units.dp(8)
        }
        Column {
            id: infoColumn
            anchors.fill: parent
            property int iconSize: Units.dp(28)
            
            ListItem.Subtitled {
                text: "账号名称"
                subText: accountInfoUsername
                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/desktop"
                    size: infoColumn.iconSize
                }
            }

            ListItem.Subtitled {
                text: "流量统计"
                subText: accountInfoFlow

                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/cloud_download"
                    size: infoColumn.iconSize
                }
            }

            ListItem.Subtitled {
                text: "登陆时长"
                subText: accountInfoTime
                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/clock_o"
                    size: infoColumn.iconSize
                }
            }

            ListItem.Subtitled {
                text: "余额"
                subText: accountInfoMoney
                secondaryItem: Button {
                    text: "充值"
                    elevation: 1
                    width: Units.dp(35)
                    onClicked: Qt.openUrlExternally("http://usereg.tsinghua.edu.cn/login.php")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/money"
                    size: infoColumn.iconSize
                }
            }
        }
    }
}
}
