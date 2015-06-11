#ifndef USER_H
#define USER_H

#include "ui.h"
#include "info.h"
#include "network.h"

#include <QWidget>
#include <QSettings>

class User : public QObject
{
    Q_OBJECT

public:
    explicit User();
    ~User();

signals:
    void loginSignal(QString username, QString password);

private:
    QString username;
    QString password;
    QSettings settings;
    void loadInfo();
    void saveInfo();

private slots:
    void loginStart(QString,QString);
};

#endif // USER_H
