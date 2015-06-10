#ifndef USER_H
#define USER_H

#include "info.h"
#include "ui.h"

#include <QWidget>
#include <QSettings>

class User : public QObject
{
    Q_OBJECT

public:
    explicit User();
    ~User();
    void loadInfo(QString&,QString&);

signals:
    void loginSignal(QString username, QString password);

private:
    QSettings settings;

private slots:
    void saveInfo(QString,QString);
};

#endif // USER_H
