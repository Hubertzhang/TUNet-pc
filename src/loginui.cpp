﻿#include <cstdio>
#include <algorithm>

#include "loginui.h"
#include "ui_loginui.h"

LoginUi::LoginUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);
    LoginUi::loadInfo();

    QFile *file = new QFile(":qss/qss/loginui.qss");
    file->open(QFile::ReadOnly);
    setStyleSheet(file->readAll());
    file->deleteLater();
    ui->password->setEchoMode(QLineEdit::Password);
    connect(ui->autoLogin, SIGNAL(stateChanged(int)),
            this, SLOT(selectSavePassword(int)));
    connect(ui->savePassword, SIGNAL(stateChanged(int)),
            this, SLOT(disselectAutoLogin(int)));
    connect(ui->loginButton, SIGNAL(clicked()),
            this, SLOT(saveInfo()));
    connect(ui->loginButton, SIGNAL(clicked()),
            this, SLOT(loginClicked()));
}

LoginUi::~LoginUi()
{

}

void LoginUi::selectSavePassword(int state)
{
    if (state == Qt::Checked)
        ui->savePassword->setCheckState(Qt::Checked);
}

void LoginUi::disselectAutoLogin(int state)
{
    if (state == Qt::Unchecked)
        ui->autoLogin->setCheckState(Qt::Unchecked);
}

void LoginUi::loadInfo()
{
    if (settings.value("SavePassword",0).toBool()) {
        ui->savePassword->setCheckState(Qt::Checked);
    }
    if (settings.value("AutoLogin",0).toBool()) {
        ui->autoLogin->setCheckState(Qt::Checked);
        autoLogin = true;
    }

    srand(42);
    
    QString encryptedUsername = settings.value("Username", QString("")).toString();
    for (int i = 0; i < encryptedUsername.length(); i++) {
        username+=(char)(encryptedUsername.at(i).toLatin1() ^ (rand() & 127));
    }
    ui->username->setText(username);

    if (ui->savePassword->checkState() != Qt::Checked)
        return;
    QString encryptedPassword = settings.value("Password", QString("")).toString();
    for (int i = 0; i < encryptedPassword.length(); i++) {
        password+=(char)(encryptedPassword.at(i).toLatin1() ^ (rand() & 127));
    }

    ui->password->setText(password);
    ui->password->setEchoMode(QLineEdit::Password);
}

void LoginUi::saveInfo()
{
    settings.setValue("SavePassword",ui->savePassword->checkState() == Qt::Checked);
    settings.setValue("AutoLogin",ui->autoLogin->checkState() == Qt::Checked);

    srand(42);
    int usernameLength = ui->username->text().length();
    QString tempUsername;
    for (int i = 0; i < usernameLength; i++) {
        tempUsername+=(ui->username->text().at(i).toLatin1() ^ (rand() & 127));
    }
    settings.setValue("Username", tempUsername);
    
    if (ui->savePassword->checkState() != Qt::Checked) {
        settings.setValue("Password",QString(""));
    } else {
        int passwordLength = ui->password->text().length();
        QString tempPassword;
        for (int i = 0; i < passwordLength; i++) {
            tempPassword+=(ui->password->text().at(i).toLatin1() ^ (rand() & 127));
        }
        settings.setValue("Password", tempPassword);
    }
    settings.sync();
}

void LoginUi::loginClicked()
{
    username = ui->username->text(); password = ui->password->text();
    emit loginSignal(ui->username->text(), ui->password->text());
}

void LoginUi::loginFailDialog(Info info)
{
    loginFail = new FailUi(info.accountInfo.error);
    loginFail->exec();
    loginFail->deleteLater();
}

void LoginUi::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}
