#ifndef CONNECTION_H
#define CONNECTION_H

#include "ui.h"
#include "info.h"
#include "network.h"
#include "dataformatter.h"

#include <QWidget>
#include <QFile>
#include <qtimer.h>
#include <QSettings>

class Connection : public QObject
{
    Q_OBJECT

public:
    explicit Connection();
    ~Connection();
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
