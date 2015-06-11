#include <QFile>
#include "account.h"

Account::Account()
{
    connection = new Connection;
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(timeIncrement()));

    //登陆成功
    connect(Network::instance(), SIGNAL(loginSucceed(Info)),
            this, SLOT(infoSlot(Info)));

    //定时查询
    connect(Network::instance(), SIGNAL(checkResult(Info)),
            this, SLOT(checkResultSlot(Info)));
    connect(Network::instance(), SIGNAL(infoSignal(Info)),
            this, SLOT(infoSlot(Info)));

    //断开
    connect(this, SIGNAL(logoutSignal()),
            Network::instance(), SLOT(logoutSlot()));

    //断开成功
    connect(Network::instance(), SIGNAL(logoutSucceed()),
            this, SLOT(onLogoutSucceed()));
}

Account::~Account()
{
}

void Account::infoSlot(Info info)
{
    if (info.infoType == Info::LoginInfo) {
        hasAccurateTraffic = false;
        roughTraffic = qMax(info.accountInfo.roughTraffic, roughTraffic);
    }
    else {
        hasAccurateTraffic = true;
        thisSessionTraffic = info.accountInfo.totalAccurateTraffic;
        Ui::instance()->rootContext()->setContextProperty("accountUsername",info.accountInfo.userName);
        Ui::instance()->rootContext()->setContextProperty("accountMoney",QString::number(info.accountInfo.balance, 'f', 2) + "RMB");
    }
    if (info.infoType == Info::QueryInfo)
        connection->show(info);
    timer->start(1000);
    lastQueryTime = 0;
    updateTraffic();
}

void Account::checkResultSlot(Info info)
{
    roughTraffic = qMax(info.accountInfo.roughTraffic, roughTraffic);
    int timeReceived = info.accountInfo.loginTime;
    if (onlineTime != timeReceived) {
        onlineTime = timeReceived;
        timer->start(1000);
    }
    updateTraffic();
}

void Account::updateTraffic()
{
    if (hasAccurateTraffic) {
        Ui::instance()->rootContext()->setContextProperty("accountFlow",DataFormatter::trafficForm(roughTraffic + thisSessionTraffic));
    }
    else {
        Ui::instance()->rootContext()->setContextProperty("accountFlow",">=" + DataFormatter::trafficForm(roughTraffic));
    }
}

void Account::timeIncrement()
{
    if (lastQueryTime > 0) {
        --lastQueryTime;
    }
    else {
        lastQueryTime = queryInterval;
        Network::instance()->check();
        Network::instance()->query();
    }
    if (onlineTime >= 0) {
        onlineTime++;
        QString timeText = DataFormatter::timeForm(onlineTime / 60 / 60) + ":" +
                           DataFormatter::timeForm(onlineTime / 60 % 60) + ":" +
                           DataFormatter::timeForm(onlineTime % 60);
        Ui::instance()->rootContext()->setContextProperty("accountTime",timeText);
    }
    else {
        Ui::instance()->rootContext()->setContextProperty("accountTime","Loading...");
    }
}

void Account::onLogoutSucceed()
{
    timer->stop();
    Ui::instance()->clear();
}
