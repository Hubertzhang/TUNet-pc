import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem

ApplicationWindow {
    id: demo
    visible: true
    width: 400
    height: 500

    theme {
        primaryColor: Palette.colors["blue"]["500"]
        primaryDarkColor: Palette.colors["blue"]["700"]
        accentColor: Palette.colors["teal"]["500"]
        tabHighlightColor: "white"
    }

    property var componentLabels: [
            "账户信息", //AccountInfo
            "在线状态" //OnlineState
    ]

    property int selectedComponent: 0

    AccountInfo {
        id: accountInfo
    }

    OnlineState {
        id: onlineState
    }

    User {
        id: user
    }

    About {
        id: about
    }

    initialPage: Page {
        id:page
        title: "Lab mU"
        actions: [
            Action {
                iconName: "awesome/user"
                name: "Account"
                onTriggered: user.show()
            },
            Action {
                iconName: "awesome/group"
                name: "About"
                onTriggered: about.show();
            }
        ]

        Sidebar {
            id: sidebar
            width: 100
            Column {
                width: parent.width
                Repeater {
                    model: 2
                    delegate: ListItem.Standard {
                        text: componentLabels[modelData]
                        selected: modelData == selectedComponent
                        onClicked: {
                            selectedComponent = modelData
                            if (selectedComponent == 0)
                                example.sourceComponent = accountInfo
                            if (selectedComponent == 1)
                                example.sourceComponent = onlineState
                         }
                    }
                }
            }
        }

        Flickable {
            id: flickable
            anchors {
                left: sidebar.right
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
            clip: true
            contentHeight: Math.max(example.implicitHeight + 40, height)
            Loader {
                id: example
                anchors.fill: parent
                sourceComponent: accountInfo
            }
            Snackbar {
                id: snackbar
            }
            function showSnackbar(message) {
                snackbar.open(message);
            }
            Connections {
                target: interfaceFrame
                onShowHint: {
                    flickable.showSnackbar(content)
                }
            }
        }

        Scrollbar {
            flickableItem: flickable
        }

    }
}
