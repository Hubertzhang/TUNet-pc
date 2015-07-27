#ifndef NETWORKINFOTYPE_H
#define NETWORKINFOTYPE_H

#include <QString>

enum ConnectionState {
    Connected = 0,
    NotInTsinghua,
    NotAccessible,
    NoConnection
};

struct IpInfo
{
    int ipv4_Ip[4];  //ip地址，
    QString onlineTimeString;//上线时间字符串,example  03-02 08:28
    int onlineTime[3];//上线时间
    QString macAdress;  //mac地址
    double accurateTraffic;  //该ip精确流量
    QString IpLogoutCookie; //下线ip用的cookie
};

struct AccountInfo
{
    QString username;
    double balance;  //账户余额
    double roughTraffic;  //粗略流量，B为单位
    double totalAccurateTraffic;  //总精确流量，B为单位
    int loginTime;  //Connected times in seconds
    int onlineIpCount;  //ip数量
    IpInfo ipInfo[3];  //ip信息
};

class Info
{
public:
    enum InfoType
    {
        InvalidInfo = 0,
        LoginInfo,
        LogoutInfo,
        QueryNetInfo,
        QueryUseregInfo,
        DropIpInfo
    };

    QString hint = "";
    InfoType infoType;
    AccountInfo accountInfo;//Currently all types of info are stored here.
};

#endif // NETWORKINFORMATIONTYPE_H
