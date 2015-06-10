#ifndef ACCOUNTUI_H
#define ACCOUNTUI_H

#include "ui.h"
#include "connectionui.h"
#include "info.h"
#include "dataformatter.h"

#include <QWidget>
#include <qtimer.h>

class AccountUi : public QObject
{
    Q_OBJECT
public:
    explicit AccountUi(ConnectionUi*);
    ~AccountUi();

public:
    int onlineTime = -1;
    bool hasAccurateTraffic = false;
    double roughTraffic = 0, thisSessionTraffic = 0;

private:
    QTimer *timer;
    ConnectionUi *connection;
    void updateTraffic();

signals:
    void logoutSignal();
    void message(QString content);

private slots:
    void timeIncrement();

public slots:
    void infoSlot(Info);
    void checkResultSlot(Info);
    void onLogoutSucceed();
};

#endif // ACCOUNTUI_H
