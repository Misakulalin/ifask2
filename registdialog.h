#ifndef REGISTDIALOG_H
#define REGISTDIALOG_H
#include"global.h"
#include <QDialog>

namespace Ui {
class RegistDialog;
}

class RegistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistDialog(QWidget *parent = nullptr);
    ~RegistDialog();


private slots:
    void on_get_code_clicked();
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);//注册发射验证码

private:
    void initHttpHandlers();
    Ui::RegistDialog *ui;
    void showTip(QString str,bool book);
    QMap<ReqId, std::function<void(const QJsonObject&)>> _hanlders;//注册消息声明
};

#endif // REGISTDIALOG_H
