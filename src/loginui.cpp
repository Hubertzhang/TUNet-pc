#include "loginui.h"

#include <cstdio>
#include <algorithm>

LoginUi::LoginUi()
{
    connect(this, SIGNAL(loginSignal(QString,QString)),
            this, SLOT(saveInfo(QString,QString)));
}

LoginUi::~LoginUi()
{

}

void LoginUi::loadInfo(QString &username, QString &password)
{
    srand(42);
    
    username="";
    QString encryptedUsername = settings.value("Username", QString("")).toString();
    for (int i = 0; i < encryptedUsername.length(); i++) {
        username+=(char)(encryptedUsername.at(i).toLatin1() ^ (rand() & 127));
    }
    ui->rootContext()->setContextProperty("userUsername",username);

    password="";
    QString encryptedPassword = settings.value("Password", QString("")).toString();
    for (int i = 0; i < encryptedPassword.length(); i++) {
        password+=(char)(encryptedPassword.at(i).toLatin1() ^ (rand() & 127));
    }
    ui->rootContext()->setContextProperty("userPassword",password);
}

void LoginUi::saveInfo(QString username,QString password)
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
