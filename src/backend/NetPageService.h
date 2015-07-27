#ifndef NETPAGE_H
#define NETPAGE_H

#include "NetworkInfoType.h"
#include "BasicNetworkService.h"
#include <QtNetwork>

class NetPageService : public QObject
{
    Q_OBJECT

public:
    static NetPageService* instance();
    static NetPageService *_instance;
    void loginRequest(QString,QString);
    void logoutRequest();
    void queryStateRequest();

private:
    QNetworkAccessManager *manager = NULL;
    QNetworkReply *loginReply = NULL;
    QNetworkReply *logoutReply = NULL;
    QNetworkReply *queryStateReply = NULL;
    Info loginInfo;
    Info logoutInfo;
    Info queryStateInfo;

signals:
    void loginResult(Info);
    void logoutResult(Info);
    void queryStateResult(Info);

public slots:
    void loginRequestFinished();
    void logoutRequestFinished();
    void queryStateRequestFinished();
};

#endif // NETPAGE_H
