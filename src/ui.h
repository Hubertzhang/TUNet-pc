#ifndef UI_H
#define UI_H

#include <QQmlContext>
#include <QQmlApplicationEngine>

class Ui : public QQmlApplicationEngine
{
    Ui();
public:
    static Ui* instance();
    static Ui *_instance;
    void clear();
};

#endif
