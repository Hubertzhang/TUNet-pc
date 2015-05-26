#ifndef LOGINUI_H
#define LOGINUI_H

#include "info.h"
#include "ui.h"

#include <QWidget>
#include <QtNetwork>
#include <QSettings>

extern Ui *ui;

class LoginUi : public QObject
{
    Q_OBJECT

public:
    explicit LoginUi();
    ~LoginUi();
    void loadInfo(QString&,QString&);

signals:
    void loginSignal(QString username, QString password);

private:
    QString url;
    QSettings settings;

private slots:
    void saveInfo(QString,QString);
};

#endif // LOGINUI_H
