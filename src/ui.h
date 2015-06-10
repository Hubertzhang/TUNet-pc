#ifndef UI_H
#define UI_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>

class Ui : public QQmlApplicationEngine
{
    Q_OBJECT

    Ui();
signals:
    void message(QString content);

public:
    static Ui* instance();
    static Ui *_instance;
    void clear();
};

#endif
