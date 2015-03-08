#ifndef INFO_H
#define INFO_H

#include <QString>

struct IpInfo
{
    int ipv4_Ip[4];  //ip��ַ��
    int onlineTime[3];  //����ʱ��,ʱ���룬��
    QString macAdress;  //mac��ַ
    double accurateTraffic;  //��ip��ȷ����
};

struct AccountInfo
{
    QString error = "";  //Empty string when there's no error. Otherwise some description of the error.
    QString userName;
    double balance;  //�˻����
    double roughTraffic;  //����������BΪ��λ
    double totalAccurateTraffic;  //�ܾ�ȷ������BΪ��λ
    int loginTime;  //Connected times in seconds
    int onlineIpCount;  //ip����
    IpInfo *ipInfo;  //ip��Ϣ
};


class Info
{
public:
    Info();
    ~Info();

    enum InfoType
    {
        LoginInfo = 0,
        LogoutInfo,
        QueryInfo,
        CheckInfo
    };
    
    InfoType infoType;
    AccountInfo *accountInfo;//Currently all types of info are stored here.
};

#endif // INFO_H
