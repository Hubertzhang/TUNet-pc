#include <QFile>
#include "accountui.h"

AccountUi::AccountUi(ConnectionUi *connectionUi)
{
    connection = connectionUi;
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(timeIncrement()));
}

AccountUi::~AccountUi()
{
}

void AccountUi::infoSlot(Info info)
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

void AccountUi::checkResultSlot(Info info)
{
    roughTraffic = qMax(info.accountInfo.roughTraffic, roughTraffic);
    int timeReceived = info.accountInfo.loginTime;
    if (onlineTime != timeReceived) {
        onlineTime = timeReceived;
        timer->start(1000);
    }
    updateTraffic();
}

void AccountUi::updateTraffic()
{
    if (hasAccurateTraffic) {
        Ui::instance()->rootContext()->setContextProperty("accountFlow",DataFormatter::trafficForm(roughTraffic + thisSessionTraffic));
    }
    else {
        Ui::instance()->rootContext()->setContextProperty("accountFlow",">=" + DataFormatter::trafficForm(roughTraffic));
    }
}

void AccountUi::timeIncrement()
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

void AccountUi::onLogoutSucceed()
{
    timer->stop();
    Ui::instance()->clear();
}
