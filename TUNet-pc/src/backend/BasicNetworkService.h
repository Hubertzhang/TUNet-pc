#ifndef BASICNETWORKSERVICE_H
#define BASICNETWORKSERVICE_H

#include "NetworkInfoType.h"
#include <QHostInfo>
#include <QNetworkSession>
#include <QNetworkAccessManager>

class BasicNetworkService
{
public:
    static ConnectionState checkConnection();
    static QString getMac();

private:
    static QNetworkAccessManager *manager;
};

#endif // BASICNETWORKSERVICE_H
