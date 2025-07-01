#include "registdialog.h"
#include "ui_registdialog.h"
#include"global.h"
#include <QRegularExpression>
RegistDialog::RegistDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistDialog)
{
    ui->setupUi(this);

    QList<QLabel*> labels_to_align;//创建标签数组
    labels_to_align<<ui->label<<ui->password_1<<ui->confirmed_1<<ui->email;//将要更改的label传入
    int max_width=0;//创建来计算最宽的像素
    for(auto label:labels_to_align)
    {
        max_width=std::max(max_width,label->fontMetrics().horizontalAdvance(label->text()));
    }//获取最宽的像素
    for(auto label:labels_to_align)
    {
        label->setMinimumWidth(max_width + 5);
    }
    this->setStyleSheet(//添加主界面的图片
        "#RegistDialog { "
        "    border-image: url(:/ico/01.png); "
        "}");
    ui->password_2->setEchoMode(QLineEdit::Password);//将确认密码和输入密码都设置为不可见模式
    ui->confirmed_2->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state","normal");//设置错误提示的状态
    repolish(ui->err_tip);
    connect(ui->qpush,&QPushButton::clicked,this,&RegistDialog::on_get_code_clicked);//按钮连接发送验证码
}

 void RegistDialog::on_get_code_clicked()//槽函数的实现
{
     //验证邮箱的地址正则表达式
     auto email = ui->email_edit->text();
     // 邮箱地址的正则表达式
     QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
     bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
     if(match){
         //发送http请求获取验证码
     }else{
         //提示邮箱不正确
         showTip(tr("邮箱地址不正确"));
     }
}
void RegistDialog::showTip(QString str)
{
    ui->err_tip->setText(str);
    ui->err_tip->setProperty("state","err");
    repolish(ui->err_tip);
}

// void RegistDialog::on_sure_clicked()
// {
//     auto password = ui->password_2->text();
//     if(password.isEmpty()){
//         showTip("密码不能为空");
//         return;
//     }

//     auto confirmed = ui->confirmed_2->text();
//     if(confirmed.isEmpty()){
//         showTip("确认密码不能为空");
//         return;
//     }

//     auto code = ui->verify_edit->text();
//     if(code.isEmpty()){
//         showTip("验证码不能为空");
//         return;
//     }

//     if(password != confirmed){
//         showTip("密码和确认密码不一致");
//         return;
//     }
// }
RegistDialog::~RegistDialog()
{
    delete ui;
}
