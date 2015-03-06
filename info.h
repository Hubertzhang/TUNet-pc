#ifndef INFO_H
#define INFO_H

#include <QString>
typedef struct IpInfo
{
    int ipv4_Ip[4]; //ip��ַ��
    int onlineTime[3];//����ʱ��,ʱ���룬��
    QString macAdress; //mac��ַ
    double accurateTraffic; //��ip��ȷ����
}IpInfo;

typedef struct AccountInfo
{
    QString userName;
    double balance;//�˻����
    double roughTraffic;//����������BΪ��λ
    double totalAccurateTraffic;//�ܾ�ȷ������BΪ��λ
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
