#include "ui.h"

Ui* Ui::_instance = NULL;

Ui* Ui::instance() {
    if (_instance == NULL) {
        _instance = new Ui;
        _instance->load(QUrl(QStringLiteral("qrc:///qml/qml/Main.qml")));
        _instance->rootContext()->setContextProperty("ui",_instance);
        _instance->rootContext()->setContextProperty("user",new User);
        _instance->rootContext()->setContextProperty("account",new Account);
    }
    return _instance;
}

Ui::Ui() {
}

void Ui::clear() {
    rootContext()->setContextProperty("connectionCount",0);
    rootContext()->setContextProperty("accountUsername","");
    rootContext()->setContextProperty("accountFlow","");
    rootContext()->setContextProperty("accountTime","");
    rootContext()->setContextProperty("accountMoney","");
}
