#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "ui.h"
#include "info.h"
#include "network.h"
#include "connection.h"
#include "dataformatter.h"

#include <QWidget>
#include <qtimer.h>

class Connection;

class Account : public QObject
{
    Q_OBJECT
public:
    explicit Account();
    ~Account();

public:
    int queryInterval = 30;
    int lastQueryTime;
    int onlineTime = -1;
    bool hasAccurateTraffic = false;
    double roughTraffic = 0, thisSessionTraffic = 0;

private:
    QTimer *timer;
    Connection *connection;
    void updateTraffic();

signals:
    void logoutSignal();

private slots:
    void timeIncrement();
    void onLogoutSucceed();
    void onDropIpSucceed();

public slots:
    void infoSlot(Info);
    void checkResultSlot(Info);
};

#endif // ACCOUNT_H
