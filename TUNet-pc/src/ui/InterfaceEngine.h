#ifndef INTERFACEENGINE
#define INTERFACEENGINE

#include <QQmlContext>
#include <QQmlApplicationEngine>

class InterfaceEngine : public QQmlApplicationEngine
{
    Q_OBJECT

public:
    static InterfaceEngine* instance();
    static InterfaceEngine *_instance;

private:
    InterfaceEngine();

signals:
    void showHint(QString content);
};

#endif // INTERFACEENGINE

