#include "ifask2.h"
#include "ui_ifask2.h"
#include<QIcon>

ifask2::ifask2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ifask2)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/ico/mainico.ico"));//窗口图标
    _new_login=new LoginDialog();//新对象
    setCentralWidget(_new_login);
    _new_login->show();//显示主界面
 connect(_new_login, &LoginDialog::switchRegister, this, &ifask2::SlotSwitchReg);//信号源_new_login，
 reg_dig=new RegistDialog();
}
void ifask2::SlotSwitchReg(){
    setCentralWidget(reg_dig);
    _new_login->hide();
    reg_dig->show();
}


ifask2::~ifask2()
{
    delete ui;
    if(_new_login)
    {

        delete _new_login;
        _new_login=nullptr;
    }
    if(reg_dig)
    {

        delete reg_dig;
         reg_dig=nullptr;
    }
}
