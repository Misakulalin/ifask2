#ifndef IFASK2_H
#define IFASK2_H
#include"logindialog.h"
#include"registdialog.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ifask2;
}
QT_END_NAMESPACE

class ifask2 : public QMainWindow
{
    Q_OBJECT

public:
    ifask2(QWidget *parent = nullptr);
    ~ifask2();

private slots:
   void SlotSwitchReg();//唤醒注册窗口的槽函数
private:
    RegistDialog*reg_dig;//一个登录类的指针

private:
    Ui::ifask2 *ui;
    LoginDialog * _new_login;
};
#endif // IFASK2_H
