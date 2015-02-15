#ifndef LOGINUI_H
#define LOGINUI_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class LoginUi;
}

class LoginUi : public QWidget
{
    Q_OBJECT

public:
    explicit LoginUi(QWidget *parent = 0);
    ~LoginUi();

signals:
    void loginSignal(QString username, QString password);

private:
    Ui::LoginUi *ui;
    QString url;
    QString username;
    QString password;
};

#endif // LOGINUI_H
