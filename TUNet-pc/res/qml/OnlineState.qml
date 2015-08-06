import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

Component {
Item {
    View {
        elevation: 1

        anchors {
            fill: parent
            margins: Units.dp(8)
        }

        Column {
            anchors.fill: parent
            Connection {
                property int number: 0
                visible: connectionCount>=1;
            }
            Connection {
                property int number: 1
                visible: connectionCount>=2;
            }
            Connection {
                property int number: 2
                visible: connectionCount>=3;
            }
        }
    }
}
}
