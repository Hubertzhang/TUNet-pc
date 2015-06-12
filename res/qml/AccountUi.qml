import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

Component {
Item {
    View {
        id: accountUi
        elevation: 1
        anchors {
            fill: parent
            margins: Units.dp(8)
        }
        Column {
            anchors.fill: parent

            ListItem.Subtitled {
                text: "账号名称"
                subText: accountUsername
                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/desktop"
                    size: Units.dp(28)
                }
                onClicked: account.logoutSignal();
            }

            ListItem.Subtitled {
                text: "流量统计"
                subText: accountFlow

                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/cloud_download"
                    size: Units.dp(28)
                }
            }

            ListItem.Subtitled {
                text: "登陆时长"
                subText: accountTime
                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/clock_o"
                    size: Units.dp(28)
                }
            }

            ListItem.Subtitled {
                text: "余额"
                subText: accountMoney
                secondaryItem: Button {
                    text: "充值"
                    elevation: 1
                    width: 32
                    onClicked: Qt.openUrlExternally("http://usereg.tsinghua.edu.cn/login.php")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/money"
                    size: Units.dp(28)
                }
            }
        }
    }
}
}
