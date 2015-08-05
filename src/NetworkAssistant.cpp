#include "NetworkAssistant.h"

NetworkAssistant::NetworkAssistant() {
    loadUsernameAndPassword();
    timer = new QTimer();
    timer->start(15000);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    accountInfoInterface = new AccountInfoInterface();
    onlineStateInterface = new OnlineStateInterface();

    NetPageService::instance()->loginRequest(username,password);
    InterfaceEngine::instance()->rootContext()->setContextProperty("networkAssistant",this);
}

NetworkAssistant::~NetworkAssistant() {
    delete timer;
}

void NetworkAssistant::loadUsernameAndPassword() {
    srand(42);

    username = "";
    QString encryptedUsername = settings.value("Username", QString("")).toString();
    for (int i = 0; i < encryptedUsername.length(); i++) {
        username += (char)(encryptedUsername.at(i).toLatin1() ^ (rand() & 127));
    }

    password = "";
    QString encryptedPassword = settings.value("Password", QString("")).toString();
    for (int i = 0; i < encryptedPassword.length(); i++) {
        password += (char)(encryptedPassword.at(i).toLatin1() ^ (rand() & 127));
    }

    InterfaceEngine::instance()->rootContext()->setContextProperty("username", username);
    InterfaceEngine::instance()->rootContext()->setContextProperty("password", password);
}

void NetworkAssistant::saveUsernameAndPassword() {
    srand(42);

    int usernameLength = username.length();
    QString tempUsername = "";
    for (int i = 0; i < usernameLength; i++) {
        tempUsername += (username.at(i).toLatin1() ^ (rand() & 127));
    }
    settings.setValue("Username", tempUsername);

    int passwordLength = password.length();
    QString tempPassword = "";
    for (int i = 0; i < passwordLength; i++) {
        tempPassword += (password.at(i).toLatin1() ^ (rand() & 127));
    }
    settings.setValue("Password", tempPassword);
}

void NetworkAssistant::onTimeOut() {
    if (BasicNetworkService::checkConnection() != Connected) {
        NetPageService::instance()->loginRequest(username, password);
    } else {
        UseregPageService::instance()->queryStateRequest(username, password);
    }
}

void NetworkAssistant::loginClicked(QString newUsername, QString newPassword)
{
    username = newUsername;
    password = newPassword;
    saveUsernameAndPassword();
    NetPageService::instance()->loginRequest(username,password);
}
