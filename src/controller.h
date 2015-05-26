#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "loginui.h"
#include "accountui.h"
#include "info.h"
#include "network.h"
#include <QtWidgets>
#include <QtQml>
#include <QFile>
#include <QDebug>

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();
    ~Controller();
    LoginUi *loginUi;
    AccountUi *accountUi;
    ConnectionUi *connectionUi;

private:
    QString username;
    QString password;
    QTimer *timer;
    Network *network;
    QMenu *trayMenu;
    QSystemTrayIcon *trayIcon;
    enum kind{change, login, loading, account} last;

signals:
    void querySignal(QString, QString);
    void checkSignal();

private slots:
    void setTimer();
    void onTimeOut();
    void onLoginStart(QString, QString);
    void onLoginSucceed();
    void onLoginFail(Info);
    void onLogoutSucceed();
    void onLogoutFail(Info);
};

#endif // CONTROLLER_H
