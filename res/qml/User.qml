import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

Dialog {
    id: user
    title: "Account setting"
    height: Units.dp(247)

    TextField {
        id: userUsername
        width: parent.width
        height: Units.dp(54)
        placeholderText: "用户名/学号"
        text: username
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextField {
        id: userPassword
        width: parent.width
        height: Units.dp(45)
        placeholderText: "密码"
        text: password
        echoMode: TextInput.Password
        anchors.horizontalCenter: parent.horizontalCenter
    }

    onAccepted: networkAssistant.loginClicked(userUsername.text,userPassword.text)
}
