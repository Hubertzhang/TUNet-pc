#ifndef UI_H
#define UI_H

#include <QQmlContext>
#include <QQmlApplicationEngine>

class Ui : public QQmlApplicationEngine
{
public:
    Ui();
    void clear();
};

#endif
