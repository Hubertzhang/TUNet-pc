#include "InterfaceEngine.h"

InterfaceEngine* InterfaceEngine::_instance = NULL;

InterfaceEngine* InterfaceEngine::instance()
{
    if (_instance == NULL) {
        _instance = new InterfaceEngine();
    }
    return _instance;
}

InterfaceEngine::InterfaceEngine()
{
    load(QUrl(QStringLiteral("qrc:///qml/qml/Main.qml")));
    rootContext()->setContextProperty("engine",this);
}
