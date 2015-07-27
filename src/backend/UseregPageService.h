#ifndef USEREGPAGE_H
#define USEREGPAGE_H

#include "NetworkInfoType.h"
#include <QtWebKit>
#include <QtNetwork>
#include <QWebFrame>
#include <QWebPage>

class UseregPageService : public QObject
{
    Q_OBJECT

public:
    static UseregPageService* instance();
    static UseregPageService *_instance;
    void queryStateRequest(QString,QString);
    void dropIpRequest(int);

private:
    enum QueryType
    {
        FirstQuery = 0,
        SecondQuery,
        ThirdQuery
    };
    QueryType queryType = FirstQuery;

    QNetworkAccessManager *manager = NULL;
    QNetworkReply *queryStateReply = NULL;
    QNetworkReply *dropIpReply = NULL;
    Info queryStateInfo;
    Info dropIpInfo;
    void getUserInfo(const QString &);
    void getIpInfo(const QString &);

signals:
    void queryStateResult(Info);
    void dropIpResult(Info);

public slots:
    void queryStateRequestFinished();
    void dropIpRequestFinished();
};

#endif // USEREGPAGE_H
