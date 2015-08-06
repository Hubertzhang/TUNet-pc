import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

Dialog {
    id: about
    title: "About us"
    property int itemHeight: Units.dp(43)
    property int itemMargin: Units.dp(2)
    ListItem.Subtitled {
        height: about.itemHeight
        margins: about.itemMargin
        text: "制作"
        subText: "叶曦 方块 蔡立崴 黄维啸 韦翼龙 庄天翼"
    }
    ListItem.Subtitled {
        height: about.itemHeight
        margins: about.itemMargin
        text: "设计"
        subText: "方块 黄维啸 韦翼龙"
    }
    ListItem.Subtitled {
        height: about.itemHeight
        margins: about.itemMargin
        text: "测试"
        subText: "何钦尧 岳大禹 张阳坤"
    }
}
