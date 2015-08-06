#ifndef NETWORKASSISTANT_H
#define NETWORKASSISTANT_H

#include "backend/BasicNetworkService.h"
#include "backend/NetPageService.h"
#include "backend/UseregPageService.h"
#include "backend/NetworkInfoType.h"
#include "ui/InterfaceEngine.h"
#include "ui/AccountInfoInterface.h"
#include "ui/OnlineStateInterface.h"
#include <QWidget>
#include <QTimer>
#include <QSettings>

class NetworkAssistant : public QObject
{
    Q_OBJECT

public:
    NetworkAssistant();
    ~NetworkAssistant();

private:
    AccountInfoInterface *accountInfoInterface;
    OnlineStateInterface *onlineStateInterface;
    QTimer *timer;
    QString username;
    QString password;
    QSettings settings;
    bool autoService = false;
    void loadUsernameAndPassword();
    void saveUsernameAndPassword();

private slots:
    void onTimeOut();

public slots:
    void loginClicked(QString, QString);
};

#endif // NETWORKASSISTANT_H
