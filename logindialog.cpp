#include "logindialog.h"
#include "ui_logindialog.h"
#include "registdialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->regist_pushButton,&QPushButton::clicked,this,&LoginDialog::switchRegister);
    this->setStyleSheet(
        "#LoginDialog { "
        "    border-image: url(:/ico/01.png); "
        "}");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}





