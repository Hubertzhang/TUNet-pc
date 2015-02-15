#include "loginui.h"
#include "ui_loginui.h"

LoginUi::LoginUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);
}

LoginUi::~LoginUi()
{
    delete ui;
}
