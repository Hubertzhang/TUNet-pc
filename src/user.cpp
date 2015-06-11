#include "user.h"

#include <cstdio>
#include <algorithm>

User::User()
{
    connect(this, SIGNAL(loginSignal(QString,QString)),
            this, SLOT(loginStart(QString,QString)));

    loadInfo();
}

User::~User()
{

}

void User::loginStart(QString _username, QString _password)
{
    username=_username;
    password=_password;
    Network::connectionState state = Network::instance()->checkConnection();
    if (state == Network::Connected) {
        Network::instance()->loginSlot(username, password);
    }
}

void User::loadInfo()
{
    srand(42);

    username="";
    QString encryptedUsername = settings.value("Username", QString("")).toString();
    for (int i = 0; i < encryptedUsername.length(); i++) {
        username+=(char)(encryptedUsername.at(i).toLatin1() ^ (rand() & 127));
    }
    Ui::instance()->rootContext()->setContextProperty("userUsername",username);

    password="";
    QString encryptedPassword = settings.value("Password", QString("")).toString();
    for (int i = 0; i < encryptedPassword.length(); i++) {
        password+=(char)(encryptedPassword.at(i).toLatin1() ^ (rand() & 127));
    }
    Ui::instance()->rootContext()->setContextProperty("userPassword",password);
}

void User::saveInfo()
{
    srand(42);

    int usernameLength = username.length();
    QString tempUsername="";
    for (int i = 0; i < usernameLength; i++) {
        tempUsername+=(username.at(i).toLatin1() ^ (rand() & 127));
    }
    settings.setValue("Username", tempUsername);

    int passwordLength = password.length();
    QString tempPassword="";
    for (int i = 0; i < passwordLength; i++) {
        tempPassword+=(password.at(i).toLatin1() ^ (rand() & 127));
    }
    settings.setValue("Password", tempPassword);
}
