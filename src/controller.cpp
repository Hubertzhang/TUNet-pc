#include "controller.h"

Controller::Controller()
{
    user = new User;
    connection = new Connection;
    account = new Account(connection);

    timer = new QTimer;
    timer->stop();
    user->loadInfo(username,password);

    //登陆
    connect(user, SIGNAL(loginSignal(QString,QString)),
            this, SLOT(onLoginStart(QString,QString)));

    //登陆成功
    connect(Network::instance(), SIGNAL(loginSucceed(Info)),
            account, SLOT(infoSlot(Info)));
    connect(Network::instance(), SIGNAL(loginSucceed(Info)),
            this, SLOT(onLoginSucceed()));
    connect(Network::instance(), SIGNAL(loginSucceed(Info)),
            this, SLOT(setTimer()));

    //定时查询
    connect(timer, SIGNAL(timeout()),
            this, SLOT(onTimeOut()));
    connect(this, SIGNAL(checkSignal()),
            Network::instance(), SLOT(checkSlot()));
    connect(Network::instance(), SIGNAL(checkResult(Info)),
            account, SLOT(checkResultSlot(Info)));
    connect(this, SIGNAL(querySignal(QString, QString)),
            Network::instance(), SLOT(querySlot(QString, QString)));
    connect(Network::instance(), SIGNAL(infoSignal(Info)),
            account, SLOT(infoSlot(Info)));

    //下线IP
    connect(connection, SIGNAL(logoutRequest(int)),
            Network::instance(), SLOT(dropIpSlot(int)));
    connect(Network::instance(), SIGNAL(dropIpSucceed()),
            this, SLOT(onTimeOut()));

    //断开
    connect(account, SIGNAL(logoutSignal()),
            Network::instance(), SLOT(logoutSlot()));

    //断开成功
    connect(Network::instance(), SIGNAL(logoutSucceed()),
            account, SLOT(onLogoutSucceed()));
    connect(Network::instance(), SIGNAL(logoutSucceed()),
            timer, SLOT(stop()));

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
    Network::connectionState state = Network::instance()->checkConnection();
    if (state == Network::Connected) {
        Network::instance()->loginSlot(username, password);
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
        emit Ui::instance()->message(errorString);
    }
}

void Controller::onLoginSucceed()
{
    emit checkSignal();
    emit querySignal(username, password);
}

Controller::~Controller()
{
}

