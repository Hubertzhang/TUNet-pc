import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

Dialog {
    id: aboutUi
    title: "About us"
    ListItem.Subtitled {
        height: 40
        margins: Units.dp(2)
        text: "制作"
        subText: "叶曦 方块 蔡立崴 黄维啸"
    }
    ListItem.Subtitled {
        height: 40
        margins: Units.dp(2)
        text: "设计"
        subText: "方块 黄维啸"
    }
    ListItem.Subtitled {
        height: 40
        margins: Units.dp(2)
        text: "测试"
        subText: "何钦尧 岳大禹 张阳坤"
    }
}
