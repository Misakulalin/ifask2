#include "ifask2.h"
#include "ui_ifask2.h"
#include<QIcon>

ifask2::ifask2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ifask2)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/ico/mainico.ico"));//窗口图标
    _new_login=new LoginDialog(this);//新对象
    setCentralWidget(_new_login);
    _new_login->show();//显示主界面
 connect(_new_login, &LoginDialog::switchRegister, this, &ifask2::SlotSwitchReg);//信号源_new_login，
 reg_dig=new RegistDialog(this);//两个新对象都使用this指针后会出现两个窗口，这时候需要做的就是对这两个窗口进行处理
 _new_login->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);//窗口将没有标题栏和边框，用户也无法通过常规的系统操作来移动或缩放窗口。
 reg_dig->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);//使用这两个方法就可以隐藏窗口了
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
