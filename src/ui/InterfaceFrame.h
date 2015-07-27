#ifndef INTERFACEFRAME_H
#define INTERFACEFRAME_H

#include <QString>
#include <QQmlContext>
#include <QQmlApplicationEngine>

class InterfaceFrame : public QObject
{
    Q_OBJECT

public:
    InterfaceFrame();

private:
    QQmlApplicationEngine *engine;

signals:
    void showHint(QString content);
};

#endif // INTERFACEFRAME_H
