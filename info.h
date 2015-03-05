#ifndef INFO_H
#define INFO_H

#include <QString>
typedef struct IpInfo
{
    int ipv4_Ip[3]; //ip��ַ
    QString macAdress; //mac��ַ
    double accurateTraffic; //��ip��ȷ����
}IpInfo;

typedef struct AccountInfo
{
    QString userName;
    double balance;//�˻����
    double totalAccurateTraffic;//�ܾ�ȷ����
    int onlineIpCount;//ip����
    IpInfo *ipInfo;//ip��Ϣ
}AccountInfo;


class Info
{
public:
    Info();
    ~Info();
public:
    enum InfoType
    {
        LoginInfo = 0,
        LogoutInfo,
        QueryInfo
    };
    InfoType infoType;
    AccountInfo *accountInfo;
};

#endif // INFO_H
