#include "controller.h"
#include "ui.h"
#include <QApplication>

Ui *ui;

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Lab mU");
    QCoreApplication::setOrganizationDomain("lab.mu");
    QCoreApplication::setApplicationName("tunet");
    QApplication a(argc, argv);
    try {
        ui = new Ui;
        ui->clear();
        Controller controller;
        ui->rootContext()->setContextProperty("loginUi",controller.loginUi);
        ui->rootContext()->setContextProperty("connectionUi",controller.connectionUi);
        ui->rootContext()->setContextProperty("accountUi",controller.accountUi);
        ui->rootContext()->setContextProperty("ui",ui);
        emit controller.accountUi->message("Welcome back!");
        return a.exec();
    }
    catch(std::exception e){
        QMessageBox *msg = new QMessageBox(QMessageBox::Critical, "Boom!",
            QString("TUNet exploded because ") + QString(e.what()), QMessageBox::Ok);
        msg->exec();
    }
}

