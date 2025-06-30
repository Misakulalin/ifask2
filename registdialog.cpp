#include "registdialog.h"
#include "ui_registdialog.h"

RegistDialog::RegistDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistDialog)
{
    ui->setupUi(this);

    QList<QLabel*> labels_to_align;//创建标签数组
    labels_to_align<<ui->label<<ui->password_1<<ui->confirmed_1<<ui->label_4;//将要更改的label传入
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

}

RegistDialog::~RegistDialog()
{
    delete ui;
}
