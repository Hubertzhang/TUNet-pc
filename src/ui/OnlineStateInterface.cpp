#include "OnlineStateInterface.h"

OnlineStateInterface::OnlineStateInterface()
{
    connect(UseregPageService::instance(),SIGNAL(queryStateResult(Info)),
            this,SLOT(useregPageQueryState(Info)));
    connect(UseregPageService::instance(),SIGNAL(dropIpResult(Info)),
            this,SLOT(useregPageDropIp(Info)));
    initializeInterface();
}

void OnlineStateInterface::initializeInterface()
{
    QQmlContext *context=InterfaceEngine::instance()->rootContext();
    context->setContextProperty("connectionCount",0);
    for (int i=0;i<3;++i)
    {
        context->setContextProperty(QString("connectionIp%1").arg(i),"");
        context->setContextProperty(QString("connectionAddress%1").arg(i),"");
        context->setContextProperty(QString("connectionTime%1").arg(i),"");
        context->setContextProperty(QString("connectionTraffic%1").arg(i),"");
        context->setContextProperty(QString("connectionName%1").arg(i),"");
    }
}

void OnlineStateInterface::useregPageQueryState(Info info)
{
    InterfaceEngine::instance()->showHint(info.hint);
    if (info.infoType==Info::InvalidInfo) return;
    InterfaceEngine::instance()->rootContext()->setContextProperty("connectionCount",info.accountInfo.onlineIpCount);
    for (int i = 0; i < info.accountInfo.onlineIpCount; ++i)
    {
        InterfaceEngine::instance()->rootContext()->setContextProperty(
            QString("connectionIp%1").arg(i),
            QString("%1.%2.%3.%4")
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[0])
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[1])
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[2])
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[3])
        );
        InterfaceEngine::instance()->rootContext()->setContextProperty(
            QString("connectionAddress%1").arg(i),
            info.accountInfo.ipInfo[i].macAdress
        );
        InterfaceEngine::instance()->rootContext()->setContextProperty(
            QString("connectionTime%1").arg(i),
            DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[0]) + ":" +
            DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[1]) + ":" +
            DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[2])
        );
        InterfaceEngine::instance()->rootContext()->setContextProperty(
            QString("connectionTraffic%1").arg(i),
            DataFormatter::trafficForm(info.accountInfo.ipInfo[i].accurateTraffic)
        );
    }
    loadName(&info);
}

void OnlineStateInterface::useregPageDropIp(Info info)
{
    InterfaceEngine::instance()->showHint(info.hint);
    if (info.infoType==Info::InvalidInfo) return;
    initializeInterface();
}

void OnlineStateInterface::loadName(Info *info)
{
    for (int i = 0; i < info->accountInfo.onlineIpCount; ++i)
        InterfaceEngine::instance()->rootContext()->setContextProperty(
            QString("connectionName%1").arg(i),
            settings.value(info->accountInfo.ipInfo[i].macAdress, "Unknown").toString()
        );
}

void OnlineStateInterface::saveName(int index,QString macAddress,QString deviceName)
{
    settings.setValue(macAddress,deviceName);
    InterfaceEngine::instance()->rootContext()->setContextProperty(
        QString("connectionName%1").arg(index),
        deviceName
    );
}

