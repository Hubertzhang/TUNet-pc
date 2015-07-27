#include "InterfaceFrame.h"

InterfaceFrame::InterfaceFrame()
{
    engine = new QQmlApplicationEngine();
    engine->load(QUrl(QStringLiteral("qrc:///qml/qml/Main.qml")));
    engine->rootContext()->setContextProperty("interfaceFrame",this);
    emit showHint("Welcome back!");
}
