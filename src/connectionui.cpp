#include "connectionui.h"

ConnectionUi::ConnectionUi()
{
    connect(this,SIGNAL(okClicked(int,QString,QString)),
            this,SLOT(saveName(int,QString,QString)));
}

ConnectionUi::~ConnectionUi()
{
}

void ConnectionUi::show(Info info)
{
    count = info.accountInfo.onlineIpCount;
    ui->rootContext()->setContextProperty("connectionCount",count);
    for (int i = 0; i < count; ++i)
    {
        ui->rootContext()->setContextProperty(
            QString("connectionIp%1").arg(i),
            QString("%1.%2.%3.%4")
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[0])
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[1])
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[2])
                .arg(info.accountInfo.ipInfo[i].ipv4_Ip[3])
        );
        ui->rootContext()->setContextProperty(
            QString("connectionAddress%1").arg(i),
            info.accountInfo.ipInfo[i].macAdress
        );
        ui->rootContext()->setContextProperty(
            QString("connectionTime%1").arg(i),
            DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[0]) + ":" +
            DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[1]) + ":" +
            DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[2])
        );
        ui->rootContext()->setContextProperty(
            QString("connectionTraffic%1").arg(i),
            DataFormatter::trafficForm(info.accountInfo.ipInfo[i].accurateTraffic)
        );
    }
    loadName(&info);
}

void ConnectionUi::loadName(Info *info)
{
    for (int i = 0; i < count; ++i)
        ui->rootContext()->setContextProperty(
            QString("connectionName%1").arg(i),
            settings.value(info->accountInfo.ipInfo[i].macAdress, "Unknown").toString()
        );
}

void ConnectionUi::saveName(int index,QString macAddress,QString deviceName)
{
    settings.setValue(macAddress,deviceName);
    ui->rootContext()->setContextProperty(
        QString("connectionName%1").arg(index),
        deviceName
    );
}
