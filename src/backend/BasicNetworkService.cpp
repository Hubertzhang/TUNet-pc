#include "BasicNetworkService.h"

QNetworkAccessManager *BasicNetworkService::manager = new QNetworkAccessManager();

ConnectionState BasicNetworkService::checkConnection()
{
    QNetworkSession ssn(manager->activeConfiguration());
    if (ssn.state() == ssn.Connected) {
        QHostInfo info = QHostInfo::fromName("www.baidu.com");
        if (info.error() == info.NoError) {
            foreach(QHostAddress addr, ssn.interface().allAddresses())
            {
                if (addr.protocol() == QAbstractSocket::IPv4Protocol
                    && (addr.isInSubnet(QHostAddress::parseSubnet("59.66.0.0/16"))
                    || addr.isInSubnet(QHostAddress::parseSubnet("166.111.0.0/16"))
                    || addr.isInSubnet(QHostAddress::parseSubnet("101.5.0.0/16"))
                    || addr.isInSubnet(QHostAddress::parseSubnet("101.6.0.0/16"))
                    || addr.isInSubnet(QHostAddress::parseSubnet("183.173.0.0/16")))) {
                    return Connected;
                }
            }
            return NotInTsinghua;
        }
        else {
            return NotAccessible;
        }
    }
    else {
        return NoConnection;
    }
}

QString BasicNetworkService::getMac()
{
    return QNetworkSession(manager->activeConfiguration()).interface().hardwareAddress();
}
