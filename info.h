#ifndef INFO_H
#define INFO_H

#include <QString>
typedef struct IpInfo
{
	QString ipv4_Ip; //ip��ַ
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
	AccountInfo accountInfo;
};

#endif // INFO_H
