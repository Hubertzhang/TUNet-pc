﻿#include "NetworkAssistant.h"
#include <QMessageBox>
#include <QApplication>

int main(int argc, char **argv) {
    QCoreApplication::setOrganizationName("Lab mU");
    QCoreApplication::setOrganizationDomain("lab.mu");
    QCoreApplication::setApplicationName("tunet");
    QApplication a(argc, argv);
    try {
        NetworkAssistant networkAssistant;
        return a.exec();
    } catch(std::exception e) {
        QMessageBox *msg = new QMessageBox(QMessageBox::Critical, "Boom!",
            QString("TUNet exploded because ") + QString(e.what()), QMessageBox::Ok);
        msg->exec();
    }
}

