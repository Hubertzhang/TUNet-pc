#include "connection.h"

Connection::Connection()
{
    connect(this,SIGNAL(okClicked(int,QString,QString)),
            this,SLOT(saveName(int,QString,QString)));
}

Connection::~Connection()
{
}

void Connection::show(Info info)
{
    count = info.accountInfo.onlineIpCount;
    Ui::instance()->rootContext()->setContextProperty("connectionCount",count);
    for (int i = 0; i < count; ++i)
    {
        Ui::instance()->rootContext()->setContextProperty(
            QString("connectionIp%1").arg(i),
            QString("%1.%2.%3.%4")
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[0])
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[1])
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[2])
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[3])
        );
        Ui::instance()->rootContext()->setContextProperty(
            QString("connectionAddress%1").arg(i),
            info.accountInfo.ipInfo[i].macAdress
        );
        Ui::instance()->rootContext()->setContextProperty(
            QString("connectionTime%1").arg(i),
            DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[0]) + ":" +
            DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[1]) + ":" +
            DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[2])
        );
        Ui::instance()->rootContext()->setContextProperty(
            QString("connectionTraffic%1").arg(i),
            DataFormatter::trafficForm(info.accountInfo.ipInfo[i].accurateTraffic)
        );
    }
    loadName(&info);
}

void Connection::loadName(Info *info)
{
    for (int i = 0; i < count; ++i)
        Ui::instance()->rootContext()->setContextProperty(
            QString("connectionName%1").arg(i),
            settings.value(info->accountInfo.ipInfo[i].macAdress, "Unknown").toString()
        );
}

void Connection::saveName(int index,QString macAddress,QString deviceName)
{
    settings.setValue(macAddress,deviceName);
    Ui::instance()->rootContext()->setContextProperty(
        QString("connectionName%1").arg(index),
        deviceName
    );
}
