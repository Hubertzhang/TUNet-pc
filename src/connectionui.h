#ifndef CONNECTIONUI_H
#define CONNECTIONUI_H

#include "ui.h"
#include "info.h"
#include "dataformatter.h"

#include <QWidget>
#include <QFile>
#include <qtimer.h>
#include <QSettings>

class ConnectionUi : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionUi();
    ~ConnectionUi();
    void show(Info);

private:
    int count;
    QSettings settings;
    void loadName(Info*);

signals:
    void logoutRequest(int);
    void okClicked(int,QString,QString);

private slots:
    void saveName(int,QString,QString);
};

#endif // CONNECTION_H
