#include "NetPageService.h"

NetPageService* NetPageService::_instance = nullptr;

NetPageService* NetPageService::instance() {
    if (_instance == nullptr) {
        _instance = new NetPageService();
        _instance->manager = new QNetworkAccessManager;
    }
    return _instance;
}

void NetPageService::loginRequest(QString username, QString password) {
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(password.toLatin1());
    QString hashedPassword = hash.result().toHex();
    QString mac = BasicNetworkService::getMac();
    QString data = "username=" + username + "&password=" + hashedPassword + "&mac=" + mac + "&drop=0&type=1&n=100";
    QNetworkRequest request(QUrl("http://net.tsinghua.edu.cn/cgi-bin/do_login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    loginReply = manager->post(request, data.toLatin1());
    connect(loginReply, SIGNAL(finished()), this, SLOT(loginFinished()));
}

void NetPageService::loginRequestFinished() {
    QNetworkReply *reply = loginReply;
    loginReply = nullptr;
    if (reply->error() == QNetworkReply::NoError) {
        QString dataReceived = reply->readAll();
        QList<QString> temp = dataReceived.split(',');
        quint64 uid = temp[0].toULongLong();
        if (uid == 0) {
            loginInfo.hint = temp[0];
            loginInfo.infoType = Info::InvalidInfo;
        } else {
            loginInfo.accountInfo.roughTraffic = temp[2].toDouble();
            loginInfo.hint = "Log in successfully";
            loginInfo.infoType = Info::LoginInfo;
        }
    }
    else {
        loginInfo.hint = reply->errorString();
        loginInfo.infoType = Info::InvalidInfo;
    }
    emit loginResult(loginInfo);
    reply->deleteLater();
}

void NetPageService::logoutRequest() {
    logoutReply = manager->get(QNetworkRequest(QUrl("http://net.tsinghua.edu.cn/cgi-bin/do_logout")));
    connect(logoutReply, SIGNAL(finished()), this, SLOT(logoutFinished()));
}

void NetPageService::logoutRequestFinished() {
    QNetworkReply *reply = logoutReply;
    logoutReply = nullptr;
    if (reply->error() == QNetworkReply::NoError) {
        QString result = reply->readAll();
        if (result == "logout_ok") {
            logoutInfo.hint = "Log out successfully";
            logoutInfo.infoType = Info::LogoutInfo;
        } else {
            logoutInfo.hint = result;
            logoutInfo.infoType = Info::InvalidInfo;
        }
    } else {
        logoutInfo.hint = reply->errorString();
        logoutInfo.infoType = Info::InvalidInfo;
    }
    emit logoutResult(logoutInfo);
    reply->deleteLater();
}

void NetPageService::queryStateRequest() {
    QNetworkRequest request(QUrl("http://net.tsinghua.edu.cn/cgi-bin/do_login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    queryStateReply = manager->post(request, "action=check_online");
    connect(queryStateReply, SIGNAL(finished()), this, SLOT(queryStateRequestFinished()));
}

void NetPageService::queryStateRequestFinished() {
    QNetworkReply *reply = queryStateReply;
    queryStateReply = nullptr;
    if (reply->error() == QNetworkReply::NoError) {
        QString dataReceived = reply->readAll();
        if (dataReceived == "") {
            queryStateInfo.hint = "not_logged_in";
            queryStateInfo.infoType = Info::InvalidInfo;
            queryStateInfo.infoType = Info::QueryNetInfo;
        }
        else {
            QList<QString> temp = dataReceived.split(',');
            queryStateInfo.accountInfo.balance = temp[2].toDouble();
            queryStateInfo.accountInfo.loginTime = temp[4].toLong();
        }
    }
    else {
        queryStateInfo.hint = reply->errorString();
        queryStateInfo.infoType = Info::InvalidInfo;
    }
    emit queryStateResult(queryStateInfo);
    reply->deleteLater();
}
