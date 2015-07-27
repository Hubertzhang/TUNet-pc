#include "UseregPageService.h"

UseregPageService* UseregPageService::_instance = NULL;

UseregPageService* UseregPageService::instance()
{
    if (_instance == NULL) {
        _instance = new UseregPageService();
        _instance->manager = new QNetworkAccessManager;
    }
    return _instance;
}

void UseregPageService::queryStateRequest(QString username, QString password)
{
    //Generate MD5 hash of the password
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(password.toLatin1());
    QString hashedPassword = hash.result().toHex();

    //设置dataInfo类型
    queryStateInfo.accountInfo.username = username;  //设置queryStateInfo的用户名

    QByteArray postData;
    QNetworkRequest request;
    postData.append("action=login");
    postData.append("&user_login_name=" + username);
    postData.append("&user_password=" + hashedPassword);
    request.setUrl(QUrl("http://usereg.tsinghua.edu.cn/do.php"));
    request.setHeader(QNetworkRequest::ContentLengthHeader, postData.length());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    queryStateReply = manager->post(request, postData);
    connect(queryStateReply, SIGNAL(finished()), this, SLOT(queryStateRequestFinished()));
    queryType = FirstQuery;
}

void UseregPageService::queryStateRequestFinished()
{
    QNetworkReply *reply = queryStateReply;
    queryStateReply = NULL;
    QString replyString;
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    replyString = codec->toUnicode((reply->readAll()));
    //读取reply
    switch (queryType) {
    case UseregPageService::FirstQuery: {
        if (replyString == "ok") {
            queryType = UseregPageService::SecondQuery;
            QNetworkRequest secondRequest;
            secondRequest.setUrl(QUrl("http://usereg.tsinghua.edu.cn/user_info.php"));
            queryStateReply = manager->get(secondRequest);
            connect(queryStateReply, SIGNAL(finished()), this, SLOT(queryStateRequestFinished()));
        }
        break;
    }

    case UseregPageService::SecondQuery: {
        getUserInfo(replyString);
        queryType = UseregPageService::ThirdQuery;
        QNetworkRequest thirdRequest;
        thirdRequest.setUrl(QUrl("http://usereg.tsinghua.edu.cn/online_user_ipv4.php"));
        queryStateReply = manager->get(thirdRequest);
        connect(queryStateReply, SIGNAL(finished()), this, SLOT(queryStateRequestFinished()));
        break;
    }

    case UseregPageService::ThirdQuery: {
        getIpInfo(replyString);
        queryStateInfo.infoType = Info::QueryNetInfo;
        emit queryStateResult(queryStateInfo);
        queryType = UseregPageService::FirstQuery;
        break;
    }

    default: {
        queryStateInfo.infoType = Info::InvalidInfo;
        emit queryStateResult(queryStateInfo);
        queryType = UseregPageService::FirstQuery;
        break;
    }
    }
    reply->deleteLater();
}

//解析http://usereg.tsinghua.edu.cn/user_info.php
//并修改信息
void UseregPageService::getUserInfo(const QString &replyString)
{
    QWebPage page;
    QWebFrame *frame = page.mainFrame();
    frame->setHtml(replyString);
    QString temp;
    QWebElement doc = frame->documentElement();
    QWebElement body = doc.findFirst("body");
    QWebElementCollection all = body.findAll("td");

    //获取余额
    temp = all[42].toPlainText();
    queryStateInfo.accountInfo.balance = temp.left(temp.length() - 3).toDouble();
    //获取登陆时流量
    temp = all[36].toPlainText();
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '(') {
            temp = temp.left(i);
            break;
        }
    }
    queryStateInfo.accountInfo.roughTraffic = 0;
    //queryStateInfo.accountInfo.roughTraffic = temp.toDouble();
    //sometimes fails on first query.
    frame->deleteLater();
}

void UseregPageService::getIpInfo(const QString &replyString)
{
    //移除注释
    QString replyStringPlus = replyString;
    replyStringPlus.remove("<!--", Qt::CaseSensitive);
    replyStringPlus.remove("-->", Qt::CaseSensitive);
    QWebPage pageSpc;
    QWebFrame *frame = pageSpc.mainFrame();
    frame->setHtml(replyStringPlus);

    QWebElement doc = frame->documentElement();
    QWebElement body = doc.findFirst("body");
    QWebElementCollection all = body.findAll("td");
    QString temp;

    queryStateInfo.accountInfo.onlineIpCount = (all.count() - 23) / 20;
    queryStateInfo.accountInfo.totalAccurateTraffic = queryStateInfo.accountInfo.roughTraffic;
    for (int i = 0; i < queryStateInfo.accountInfo.onlineIpCount; i++) {
        //ip地址
        temp = all[27 + 20 * i].toPlainText();
        int dotAdress[3];
        for (int k = 0, j = 0; k < temp.length(); k++) {
            if (temp[k] == '.') {
                dotAdress[j] = k;
                j++;
            }
        }
        queryStateInfo.accountInfo.ipInfo[i].ipv4_Ip[0] = temp.left(dotAdress[0]).toInt();
        queryStateInfo.accountInfo.ipInfo[i].ipv4_Ip[1] = temp.mid(dotAdress[0] + 1, dotAdress[1] - dotAdress[0] - 1).toInt();
        queryStateInfo.accountInfo.ipInfo[i].ipv4_Ip[2] = temp.mid(dotAdress[1] + 1, dotAdress[2] - dotAdress[1] - 1).toInt();
        queryStateInfo.accountInfo.ipInfo[i].ipv4_Ip[3] = temp.mid(dotAdress[2] + 1).toInt();

        //入流量
        temp = all[28 + 20 * i].toPlainText();
        queryStateInfo.accountInfo.ipInfo[i].accurateTraffic = temp.left(temp.length() - 1).toDouble();
        if (temp[temp.length() - 1] == 'K') {
            queryStateInfo.accountInfo.ipInfo[i].accurateTraffic *= 1000;
        }
        if (temp[temp.length() - 1] == 'M') {
            queryStateInfo.accountInfo.ipInfo[i].accurateTraffic *= (1000 * 1000);
        }
        if (temp[temp.length() - 1] == 'G') {
            queryStateInfo.accountInfo.ipInfo[i].accurateTraffic *= (1000 * 1000 * 1000);
        }
        queryStateInfo.accountInfo.totalAccurateTraffic += queryStateInfo.accountInfo.ipInfo[i].accurateTraffic;

        //时间
        temp = all[38 + 20 * i].toPlainText();
        queryStateInfo.accountInfo.ipInfo[i].onlineTimeString = temp.mid(5, 11);
        queryStateInfo.accountInfo.ipInfo[i].onlineTime[0] = temp.mid(temp.length() - 8, 2).toInt();
        queryStateInfo.accountInfo.ipInfo[i].onlineTime[1] = temp.mid(temp.length() - 5, 2).toInt();
        queryStateInfo.accountInfo.ipInfo[i].onlineTime[2] = temp.mid(temp.length() - 2, 2).toInt();
        //mac
        temp = all[41 + 20 * i].toPlainText();
        queryStateInfo.accountInfo.ipInfo[i].macAdress = temp;
        //coockie
        temp = all[42 + 20 * i].firstChild().attribute("onclick");
        queryStateInfo.accountInfo.ipInfo[i].IpLogoutCookie = temp.mid(temp.length() - 35, 32);
    }
    frame->deleteLater();
}

void UseregPageService::dropIpRequest(int IpId)
{
    QNetworkRequest dropIpRequest;
    QByteArray postData;
    QString temp;
    temp = (QString::number(queryStateInfo.accountInfo.ipInfo[IpId].ipv4_Ip[0]) + "." +
        QString::number(queryStateInfo.accountInfo.ipInfo[IpId].ipv4_Ip[1]) + "." +
        QString::number(queryStateInfo.accountInfo.ipInfo[IpId].ipv4_Ip[2]) + "." +
        QString::number(queryStateInfo.accountInfo.ipInfo[IpId].ipv4_Ip[3]));
    postData.append("action=drop&user_ip=" + temp);
    postData.append("&checksum=" + queryStateInfo.accountInfo.ipInfo[IpId].IpLogoutCookie);
    dropIpRequest.setHeader(QNetworkRequest::ContentLengthHeader, postData.length());
    dropIpRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    dropIpRequest.setUrl(QUrl("http://usereg.tsinghua.edu.cn/online_user_ipv4.php"));

    dropIpReply = manager->post(dropIpRequest, postData);
    connect(dropIpReply, SIGNAL(finished()), this, SLOT(dropIpFinished()));
}

void UseregPageService::dropIpRequestFinished()
{
    QNetworkReply *reply = dropIpReply;
    QString replyString;
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    replyString = codec->toUnicode((reply->readAll()));
    //读取reply
    if (replyString == "ok")
    {
        dropIpInfo.hint = "Drop ip successfully";
        dropIpInfo.infoType = Info::DropIpInfo;
    }
    else
    {
        dropIpInfo.hint = "Fail to drop ip";
        dropIpInfo.infoType = Info::InvalidInfo;
    }
    emit dropIpResult(dropIpInfo);
    reply->deleteLater();
}
