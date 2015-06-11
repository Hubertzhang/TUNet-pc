#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "ui.h"
#include "info.h"
#include "connection.h"
#include "dataformatter.h"

#include <QWidget>
#include <qtimer.h>

class Account : public QObject
{
    Q_OBJECT
public:
    explicit Account(Connection*);
    ~Account();

public:
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

public slots:
    void infoSlot(Info);
    void checkResultSlot(Info);
    void onLogoutSucceed();
};

#endif // ACCOUNT_H
