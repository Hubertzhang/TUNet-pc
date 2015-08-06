#ifndef ACCOUNTINFOINTERFACE_H
#define ACCOUNTINFOINTERFACE_H

#include "../backend/NetworkInfoType.h"
#include "../backend/NetPageService.h"
#include "../backend/UseregPageService.h"
#include "../DataFormatter.h"
#include "InterfaceEngine.h"
#include <QObject>
#include <QTimer>

class AccountInfoInterface : public QObject
{
    Q_OBJECT

public:
    AccountInfoInterface();
    ~AccountInfoInterface();

private:
    QTimer *timer;
    int onlineTime = -1;
    void initializeInterface();

private slots:
    void netPageLogin(Info);
    void netPageLogout(Info);
    void netPageQueryState(Info);
    void useregPageQueryState(Info);
    void useregPageDropIp(Info);
    void showOnlineTime();
};

#endif // ACCOUNTINFOINTERFACE_H
