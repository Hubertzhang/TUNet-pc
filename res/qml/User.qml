import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

Dialog {
    id: user
    title: "Account setting"
    height: 230

    TextField {
        id: username
        width: parent.width
        height: 50
        placeholderText: "用户名/学号"
        text: userUsername
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextField {
        id: password
        width: parent.width
        height: 42
        placeholderText: "密码"
        text: userPassword
        echoMode: TextInput.Password
        anchors.horizontalCenter: parent.horizontalCenter
    }

    onAccepted: loginUi.loginSignal(username.text,password.text)
}
