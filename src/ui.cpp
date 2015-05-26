#include "ui.h"

Ui::Ui() {
    load(QUrl(QStringLiteral("qrc:///qml/qml/Main.qml")));
}

void Ui::clear() {
    rootContext()->setContextProperty("connectionCount",0);
    rootContext()->setContextProperty("accountUsername","");
    rootContext()->setContextProperty("accountFlow","");
    rootContext()->setContextProperty("accountTime","");
    rootContext()->setContextProperty("accountMoney","");
}
