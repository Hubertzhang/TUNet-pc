#include "network.h"

Network* Network::_instance = NULL;

Network* Network::instance()
{
    if (_instance == NULL) {
        _instance = new Network;
        _instance->manager = new QNetworkAccessManager;
    }
    return _instance;
}

Network::Network()
{
    manager = new QNetworkAccessManager;
}

Network::~Network()
{
}

void Network::querySlot(QString username, QString password)
{
    //Generate MD5 hash of the password
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(password.toLatin1());
    QString hashedPassword = hash.result().toHex();

    //设置queryInfo类型以及实例化queryInfo
    queryInfo.infoType = Info::QueryInfo;
    queryInfo.accountInfo.userName = username;  //设置queryInfo的用户名

    QByteArray postData;
    QNetworkRequest request;
    postData.append("action=login");
    postData.append("&user_login_name=" + username);
    postData.append("&user_password=" + hashedPassword);
    request.setUrl(QUrl("http://usereg.tsinghua.edu.cn/do.php"));
    request.setHeader(QNetworkRequest::ContentLengthHeader, postData.length());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    queryReply = manager->post(request, postData);
    connect(queryReply, SIGNAL(finished()), this, SLOT(queryFinished()));
    requestType = Network::FirstQueryRequest;
}

void Network::queryFinished()
{
    QNetworkReply *reply = queryReply;
    QString replyString;
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    replyString = codec->toUnicode((reply->readAll()));
    //读取reply
    switch (requestType) {
    case Network::FirstQueryRequest: {
        if (replyString == "ok") {
            requestType = Network::SecondQueryRequest;
            QNetworkRequest secondQueryRequest;
            secondQueryRequest.setUrl(QUrl("http://usereg.tsinghua.edu.cn/user_info.php"));
            queryReply = manager->get(secondQueryRequest);
            connect(queryReply, SIGNAL(finished()), this, SLOT(queryFinished()));
        }
        break;
    }

    case Network::SecondQueryRequest: {
        getUserInfo(replyString);
        requestType = Network::ThirdQueryRequest;
        QNetworkRequest thirdQueryRequest;
        thirdQueryRequest.setUrl(QUrl("http://usereg.tsinghua.edu.cn/online_user_ipv4.php"));
        queryReply = manager->get(thirdQueryRequest);
        connect(queryReply, SIGNAL(finished()), this, SLOT(queryFinished()));
        break;
    }
            
    case Network::ThirdQueryRequest: {
        getIpInfo(replyString);
        emit infoSignal(queryInfo);
        requestType = FirstQueryRequest;
        break;
    }
            
    default: {
        break;
    }    
    }
    reply->deleteLater();
}


//解析http://usereg.tsinghua.edu.cn/user_info.php
//并修改信息
void Network::getUserInfo(const QString &replyString)
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
    queryInfo.accountInfo.balance = temp.left(temp.length() - 3).toDouble();
    //获取登陆时流量
    temp = all[36].toPlainText();
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '(') {
            temp = temp.left(i);
            break;
        }
    }
    queryInfo.accountInfo.roughTraffic = 0;
    //queryInfo.accountInfo.roughTraffic = temp.toDouble();
    //sometimes fails on first query.
    frame->deleteLater();
}

void Network::getIpInfo(const QString &replyString)
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

    queryInfo.accountInfo.onlineIpCount = (all.count() - 23) / 20;
    queryInfo.accountInfo.totalAccurateTraffic = queryInfo.accountInfo.roughTraffic;
    for (int i = 0; i < queryInfo.accountInfo.onlineIpCount; i++) {
        //ip地址
        temp = all[27 + 20 * i].toPlainText();
        int dotAdress[3];
        for (int k = 0, j = 0; k < temp.length(); k++) {
            if (temp[k] == '.') {
                dotAdress[j] = k;
                j++;
            }
        }
        queryInfo.accountInfo.ipInfo[i].ipv4_Ip[0] = temp.left(dotAdress[0]).toInt();
        queryInfo.accountInfo.ipInfo[i].ipv4_Ip[1] = temp.mid(dotAdress[0] + 1, dotAdress[1] - dotAdress[0] - 1).toInt();
        queryInfo.accountInfo.ipInfo[i].ipv4_Ip[2] = temp.mid(dotAdress[1] + 1, dotAdress[2] - dotAdress[1] - 1).toInt();
        queryInfo.accountInfo.ipInfo[i].ipv4_Ip[3] = temp.mid(dotAdress[2] + 1).toInt();
        
        //入流量
        temp = all[28 + 20 * i].toPlainText();
        queryInfo.accountInfo.ipInfo[i].accurateTraffic = temp.left(temp.length() - 1).toDouble();
        if (temp[temp.length() - 1] == 'K') {
            queryInfo.accountInfo.ipInfo[i].accurateTraffic *= 1000;
        }
        if (temp[temp.length() - 1] == 'M') {
            queryInfo.accountInfo.ipInfo[i].accurateTraffic *= (1000 * 1000);
        }
        if (temp[temp.length() - 1] == 'G') {
            queryInfo.accountInfo.ipInfo[i].accurateTraffic *= (1000 * 1000 * 1000);
        }
        queryInfo.accountInfo.totalAccurateTraffic += queryInfo.accountInfo.ipInfo[i].accurateTraffic;

        //时间
        temp = all[38 + 20 * i].toPlainText();
        queryInfo.accountInfo.ipInfo[i].onlineTimeString = temp.mid(5, 11); 
        queryInfo.accountInfo.ipInfo[i].onlineTime[0] = temp.mid(temp.length() - 8, 2).toInt();
        queryInfo.accountInfo.ipInfo[i].onlineTime[1] = temp.mid(temp.length() - 5, 2).toInt();
        queryInfo.accountInfo.ipInfo[i].onlineTime[2] = temp.mid(temp.length() - 2, 2).toInt();
        //mac
        temp = all[41 + 20 * i].toPlainText();
        queryInfo.accountInfo.ipInfo[i].macAdress = temp;
        //coockie
        temp = all[42 + 20 * i].firstChild().attribute("onclick");
        queryInfo.accountInfo.ipInfo[i].IpLogoutCookie = temp.mid(temp.length() - 35, 32);
    }
    frame->deleteLater();
}

void Network::loginSlot(QString username, QString password)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(password.toLatin1());
    QString hashedPassword = hash.result().toHex();
    QString mac = getMac();
    QString data = "username=" + username + "&password=" + hashedPassword + "&mac=" + mac + "&drop=0&type=1&n=100";
    QNetworkRequest request(QUrl("http://net.tsinghua.edu.cn/cgi-bin/do_login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    loginReply = manager->post(request, data.toLatin1());
    connect(loginReply, SIGNAL(finished()), this, SLOT(loginFinished()));
}

void Network::logoutSlot()
{
    logoutReply = manager->get(QNetworkRequest(QUrl("http://net.tsinghua.edu.cn/cgi-bin/do_logout")));
    connect(logoutReply, SIGNAL(finished()), this, SLOT(logoutFinished()));
}

void Network::checkSlot()
{
    QNetworkRequest checkRequest(QUrl("http://net.tsinghua.edu.cn/cgi-bin/do_login"));
    checkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    checkReply = manager->post(checkRequest, "action=check_online");
    connect(checkReply, SIGNAL(finished()), this, SLOT(checkFinished()));
}

void Network::loginFinished()
{
    QNetworkReply *reply = loginReply;
    loginReply = NULL;
    loginInfo.infoType = Info::LoginInfo;
    if (reply->error() == QNetworkReply::NoError) {
        QString dataReceived = reply->readAll();
        QList<QString> temp = dataReceived.split(',');
        quint64 uid = temp[0].toULongLong();
        if (uid == 0) {
            loginInfo.accountInfo.error = temp[0];
            emit Ui::instance()->message(loginInfo.accountInfo.error);
        }
        else {
            loginInfo.accountInfo.roughTraffic = temp[2].toDouble();
            emit loginSucceed(loginInfo);
            emit Ui::instance()->message("Log in successfully");
        }
    }

    else {
        loginInfo.accountInfo.error = reply->errorString();
        emit Ui::instance()->message(loginInfo.accountInfo.error);
    }
    reply->deleteLater();
}

void Network::logoutFinished()
{
    QNetworkReply *reply = logoutReply;
    Info logoutInfo;
    logoutInfo.infoType = Info::LogoutInfo;
    if (reply->error() == QNetworkReply::NoError) {
        QString result = reply->readAll();
        if (result == "logout_ok") {
            emit logoutSucceed();
            emit Ui::instance()->message("Log out successfully");
            return;
        }
        logoutInfo.accountInfo.error = result;
        emit Ui::instance()->message(logoutInfo.accountInfo.error);
    }
    else {
        logoutInfo.accountInfo.error = reply->errorString();
        emit Ui::instance()->message(logoutInfo.accountInfo.error);
    }
    reply->deleteLater();
}

void Network::checkFinished()
{
    QNetworkReply *reply = checkReply;
    Info checkInfo;
    checkInfo.infoType = Info::CheckInfo;
    if (reply->error() == QNetworkReply::NoError) {
        QString dataReceived = reply->readAll();
        if (dataReceived == "") {
            checkInfo.accountInfo.error = "not_logged_in";
            emit checkResult(checkInfo);
        }
        else {
            QList<QString> temp = dataReceived.split(',');
            checkInfo.accountInfo.balance = temp[2].toDouble();
            checkInfo.accountInfo.loginTime = temp[4].toLong();
            emit checkResult(checkInfo);
        }
    }
    else {
        checkInfo.accountInfo.error = reply->errorString();
        emit checkResult(checkInfo);
    }
    reply->deleteLater();
}

void Network::dropIpSlot(int IpId)
{
    QNetworkRequest dropIpRequest;
    QByteArray postData;
    QString temp;
    temp = (QString::number(queryInfo.accountInfo.ipInfo[IpId].ipv4_Ip[0]) + "." +
        QString::number(queryInfo.accountInfo.ipInfo[IpId].ipv4_Ip[1]) + "." +
        QString::number(queryInfo.accountInfo.ipInfo[IpId].ipv4_Ip[2]) + "." +
        QString::number(queryInfo.accountInfo.ipInfo[IpId].ipv4_Ip[3]));
    postData.append("action=drop&user_ip=" + temp);
    postData.append("&checksum=" + queryInfo.accountInfo.ipInfo[IpId].IpLogoutCookie);
    dropIpRequest.setHeader(QNetworkRequest::ContentLengthHeader, postData.length());
    dropIpRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    dropIpRequest.setUrl(QUrl("http://usereg.tsinghua.edu.cn/online_user_ipv4.php"));
    
    dropIpReply = manager->post(dropIpRequest, postData);
    connect(dropIpReply, SIGNAL(finished()), this, SLOT(dropIpFinished()));
}

void Network::dropIpFinished()
{
    QNetworkReply *reply = dropIpReply;
    QString replyString;
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    replyString = codec->toUnicode((reply->readAll()));
    //读取reply
    if (replyString == "ok")
    {
        emit dropIpSucceed();
    }
    else
    {
        emit dropIpFail();
    }
    reply->deleteLater();

}
void Network::loginAbortSlot()
{
    if (loginReply != NULL)
        loginReply->abort();
}

Network::connectionState Network::checkConnection()
{
    QNetworkSession ssn(manager->activeConfiguration());
    if (ssn.state() == ssn.Connected) {
        QHostInfo info = QHostInfo::fromName("www.baidu.com");
        if (info.error() == info.NoError) {
            foreach(QHostAddress addr, ssn.interface().allAddresses())
            {
                if (addr.protocol() == QAbstractSocket::IPv4Protocol
                    && (addr.isInSubnet(QHostAddress::parseSubnet("59.66.0.0/16"))
                    || addr.isInSubnet(QHostAddress::parseSubnet("166.111.0.0/16"))
					|| addr.isInSubnet(QHostAddress::parseSubnet("101.5.0.0/16"))
					|| addr.isInSubnet(QHostAddress::parseSubnet("101.6.0.0/16"))
                    || addr.isInSubnet(QHostAddress::parseSubnet("183.173.0.0/16")))) {
                    return Connected;
                }
            }
            return NotInTsinghua;
        }
        else {
            return NotAccessible;
        }
    }
    else {
        return NoConnection;
    }
}

QString Network::getMac()
{
    return QNetworkSession(manager->activeConfiguration()).interface().hardwareAddress();
}
