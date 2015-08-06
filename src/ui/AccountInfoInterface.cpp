#include "AccountInfoInterface.h"

AccountInfoInterface::AccountInfoInterface()
{
    connect(NetPageService::instance(),SIGNAL(loginResult(Info)),
            this,SLOT(netPageLogin(Info)));
    connect(NetPageService::instance(),SIGNAL(logoutResult(Info)),
            this,SLOT(netPageLogout(Info)));
    connect(NetPageService::instance(),SIGNAL(queryStateResult(Info)),
            this,SLOT(netPageQueryState(Info)));
    connect(UseregPageService::instance(),SIGNAL(queryStateResult(Info)),
            this,SLOT(useregPageQueryState(Info)));
    connect(UseregPageService::instance(),SIGNAL(dropIpResult(Info)),
            this,SLOT(useregPageDropIp(Info)));
    timer = new QTimer();
    timer->stop();
    onlineTime=-1;
    connect(timer,SIGNAL(timeout()),this,SLOT(showOnlineTime()));
    initializeInterface();
}

AccountInfoInterface::~AccountInfoInterface()
{
    delete timer;
}

void AccountInfoInterface::initializeInterface()
{
    InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoUsername","");
    InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoFlow","");
    InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoTime","");
    InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoMoney","");
    timer->stop();
    onlineTime=-1;
}

void AccountInfoInterface::netPageLogin(Info info)
{
    InterfaceEngine::instance()->showHint(info.hint);
    if (info.infoType==Info::InvalidInfo) return;
    InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoUsername",info.accountInfo.username);
    timer->start(1000);
}

void AccountInfoInterface::netPageLogout(Info info)
{
    InterfaceEngine::instance()->showHint(info.hint);
    if (info.infoType==Info::InvalidInfo) return;
    initializeInterface();
}

void AccountInfoInterface::netPageQueryState(Info info)
{
    InterfaceEngine::instance()->showHint(info.hint);
    if (info.infoType==Info::InvalidInfo) return;
    InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoUsername",info.accountInfo.username);
    InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoFlow",">=" + DataFormatter::trafficForm(info.accountInfo.roughTraffic));
    onlineTime=info.accountInfo.loginTime;
    timer->start(1000);
}

void AccountInfoInterface::useregPageQueryState(Info info)
{
    InterfaceEngine::instance()->showHint(info.hint);
    if (info.infoType==Info::InvalidInfo) return;
    InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoUsername", info.accountInfo.username);
    InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoFlow", DataFormatter::trafficForm(info.accountInfo.roughTraffic + info.accountInfo.totalAccurateTraffic));
    InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoMoney", QString::number(info.accountInfo.balance, 'f', 2) + "RMB");
}

void AccountInfoInterface::useregPageDropIp(Info info)
{
    InterfaceEngine::instance()->showHint(info.hint);
    if (info.infoType==Info::InvalidInfo) return;
    initializeInterface();
}

void AccountInfoInterface::showOnlineTime()
{
    if (onlineTime>=0) {
        onlineTime++;
        QString timeText = DataFormatter::timeForm(onlineTime / 60 / 60) + ":" +
                           DataFormatter::timeForm(onlineTime / 60 % 60) + ":" +
                           DataFormatter::timeForm(onlineTime % 60);
        InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoTime",timeText);
    }
    else {
        InterfaceEngine::instance()->rootContext()->setContextProperty("accountInfoTime","Loading...");
    }
}
