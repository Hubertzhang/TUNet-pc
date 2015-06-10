#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "user.h"
#include "account.h"
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
    User *user;
    Account *account;
    Connection *connection;

private:
    QString username;
    QString password;
    QTimer *timer;
    Network *network;
    QMenu *trayMenu;
    QSystemTrayIcon *trayIcon;

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
