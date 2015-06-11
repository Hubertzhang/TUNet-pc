#ifndef NETWORK_H
#define NETWORK_H

#include "ui.h"
#include "info.h"
#include <QtNetwork>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>

class Network : public QObject
{
    Q_OBJECT

public:
    static Network* instance();
    static Network *_instance;
    Network();
    ~Network();
    enum connectionState
    {
        Connected = 0,
        NotInTsinghua,
        NotAccessible,
        NoConnection
    };
    QString getMac();
    connectionState checkConnection();
private:
    QNetworkAccessManager *manager;
    QNetworkReply *queryReply, *loginReply = NULL, *logoutReply, *checkReply, *dropIpReply;
    QString username;
    QString password;

    enum RequestType
    {
        FirstQueryRequest=0,
        SecondQueryRequest,
        ThirdQueryRequest,
    };

    RequestType requestType = FirstQueryRequest; 
    Info queryInfo, loginInfo;
    void getUserInfo(const QString &replyString);
    void getIpInfo(const QString &replyString);

public:
    void query();
    void check();  //Check whether logged in, and get conneted time.
public slots:
    void loginSlot(QString, QString);
    void logoutSlot();
    void loginAbortSlot(); //Abort login
    void dropIpSlot(int);
private slots:
    void queryFinished();
    void loginFinished();
    void logoutFinished();
    void checkFinished();
    void dropIpFinished();
signals:
    void infoSignal(Info);
    void loginSucceed(Info);
    void logoutSucceed();
    void loginFail(Info);
    void logoutFail(Info);
    void checkResult(Info);
    void dropIpSucceed();
    void dropIpFail();
};

#endif // NETWORK_H
