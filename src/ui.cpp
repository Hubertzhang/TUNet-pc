#include "ui.h"

Ui* Ui::_instance = NULL;

Ui* Ui::instance() {
    if (_instance == NULL) {
        _instance = new Ui;
        _instance->load(QUrl(QStringLiteral("qrc:///qml/qml/Main.qml")));
    }
    return _instance;
}

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
