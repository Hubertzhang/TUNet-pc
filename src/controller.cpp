﻿#include "controller.h"

Controller::Controller()
{
    network = new Network;
    loginUi = new LoginUi;
    connectionUi = new ConnectionUi;
    accountUi = new AccountUi(connectionUi);

    timer = new QTimer;
    timer->stop();
    loginUi->loadInfo(username,password);

    /*
    createTrayMenu();
    trayIcon = new QSystemTrayIcon;
    trayIcon->setContextMenu(trayMenu);
    trayIcon->setIcon(QIcon(":/imgs/images/logo.png"));
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));
    */

    //登陆
    connect(loginUi, SIGNAL(loginSignal(QString,QString)),
            this, SLOT(onLoginStart(QString,QString)));

    //登陆成功
    connect(network, SIGNAL(loginSucceed(Info)),
            accountUi, SLOT(infoSlot(Info)));
    connect(network, SIGNAL(loginSucceed(Info)),
            this, SLOT(onLoginSucceed()));
    connect(network, SIGNAL(loginSucceed(Info)),
            this, SLOT(setTimer()));
    
    //登录失败
    connect(network, SIGNAL(loginFail(Info)),
            this, SLOT(onLoginFail(Info)));

    //定时查询
    connect(timer, SIGNAL(timeout()),
            this, SLOT(onTimeOut()));
    connect(this, SIGNAL(checkSignal()),
            network, SLOT(checkSlot()));
    connect(network, SIGNAL(checkResult(Info)),
            accountUi, SLOT(checkResultSlot(Info)));
    connect(this, SIGNAL(querySignal(QString, QString)),
            network, SLOT(querySlot(QString, QString)));
    connect(network, SIGNAL(infoSignal(Info)),
            accountUi, SLOT(infoSlot(Info)));

    //下线IP
    connect(connectionUi, SIGNAL(logoutRequest(int)),
            network, SLOT(dropIpSlot(int)));
    connect(network, SIGNAL(dropIpSucceed()),
            this, SLOT(onTimeOut()));

    //断开
    connect(accountUi, SIGNAL(logoutSignal()),
            network, SLOT(logoutSlot()));

    //断开成功
    connect(network, SIGNAL(logoutSucceed()),
            this, SLOT(onLogoutSucceed()));
    connect(network, SIGNAL(logoutSucceed()),
            accountUi, SLOT(onLogoutSucceed()));
    connect(network, SIGNAL(logoutSucceed()),
            timer, SLOT(stop()));

    //断开失败
    connect(network, SIGNAL(logoutFail(Info)),
            this, SLOT(onLogoutFail(Info)));
}

void Controller::setTimer()
{
    timer->start(30000);
}

void Controller::onTimeOut()
{
    emit checkSignal();
    emit querySignal(username, password);
}

void Controller::onLoginStart(QString username,QString password)
{
    this->username=username;
    this->password=password;
    Network::connectionState state = network->checkConnection();
    if (state == Network::Connected) {
        network->loginSlot(username, password);
    }
    else {
        QString errorString;
        switch (state) {
        case Network::NoConnection:
            errorString = "No Connection";
            break;
        case Network::NotAccessible:
            errorString = "Cannot connect to Internet";
            break;
        case Network::NotInTsinghua:
            errorString = "Not in Tsinghua network";
            break;
        }
        emit accountUi->message(errorString);
    }
}

void Controller::onLoginSucceed()
{
    emit checkSignal();
    emit querySignal(username, password);
    emit accountUi->message("Log in successfully");
}

void Controller::onLoginFail(Info info)
{
    emit accountUi->message(info.accountInfo.error);
}

void Controller::onLogoutSucceed()
{
    emit accountUi->message("Log out successfully");
}

void Controller::onLogoutFail(Info info)
{
    emit accountUi->message(info.accountInfo.error);
}

Controller::~Controller()
{
}

