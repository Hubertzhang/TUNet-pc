#include "controller.h"
#include "ui.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QCoreApplication::setOrganizationName("Lab mU");
    QCoreApplication::setOrganizationDomain("lab.mu");
    QCoreApplication::setApplicationName("tunet");
    QApplication a(argc, argv);
    try {
        Controller controller;
        Ui::instance()->rootContext()->setContextProperty("loginUi",controller.loginUi);
        Ui::instance()->rootContext()->setContextProperty("connectionUi",controller.connectionUi);
        Ui::instance()->rootContext()->setContextProperty("accountUi",controller.accountUi);
        Ui::instance()->clear();
        emit controller.accountUi->message("Welcome back!");
        return a.exec();
    }
    catch(std::exception e){
        QMessageBox *msg = new QMessageBox(QMessageBox::Critical, "Boom!",
            QString("TUNet exploded because ") + QString(e.what()), QMessageBox::Ok);
        msg->exec();
    }
}

