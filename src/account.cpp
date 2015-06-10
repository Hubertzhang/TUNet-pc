﻿#include <QFile>
#include "account.h"

Account::Account(Connection *_connection)
{
    connection = _connection;
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(timeIncrement()));
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