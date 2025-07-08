#include "registdialog.h"
#include "ui_registdialog.h"
#include"global.h"
#include"httpmgr.h" //网络请求类
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
    connect(ui->get_code,&QPushButton::clicked,this,&RegistDialog::on_get_code_clicked);//按钮连接发送验证码
    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_reg_mod_finish,this,
            &RegistDialog::slot_reg_mod_finish);//网络请求检查通过，检测发射的网络请求并启动相关槽函数
    
    // 初始化HTTP处理器
    initHttpHandlers();
}

 void RegistDialog::on_get_code_clicked()//槽函数的实现
{
     qDebug()<<"receive varify btn clicked ";
     //验证邮箱的地址正则表达式
     auto email = ui->email_edit->text();
     // 邮箱地址的正则表达式
     QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
     bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
     if(match){
         //发送http请求获取验证码,点击获取验证码的槽函数里添加发送http的post请求
         QJsonObject json_obj;
         json_obj["email"] = email;
         HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/get_varifycode"),
                                json_obj, ReqId::ID_GET_VARIFY_CODE,Modules::REGISTERMOD);
     }else{
         //提示邮箱不正确
         showTip(tr("邮箱地址不正确"),false);
     }
}
void RegistDialog::showTip(QString str,bool b_ok)
{
    if(b_ok){
        ui->err_tip->setProperty("state","normal");
    }else{
        ui->err_tip->setProperty("state","err");
    }

    ui->err_tip->setText(str);

    repolish(ui->err_tip);
}

void RegistDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err !=ErrorCodes::SUCCESS)
    {
        showTip(tr("网络请求错误"),false);
        return;
    }
    
    qDebug() << "Received response:" << res; // 调试输出
    
    //解析字符串，res并转换。
    QJsonDocument jsonDoc=QJsonDocument::fromJson(res.toUtf8());//将字符转换成utf8的格式
    if(jsonDoc.isEmpty())
    {
        showTip(tr("解析失败"),false);
        return;
    }
    //json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }
    
    //调用对应的逻辑,根据id回调。
    if(_hanlders.contains(id)) {
        _hanlders[id](jsonDoc.object());
    } else {
        qDebug() << "No handler found for request ID:" << id;
        showTip(tr("未知的请求类型"),false);
    }
}

void RegistDialog::initHttpHandlers()
{
    //获取验证码,_handler对象在构造函数中要先创建，不然这就是一个空对象会报错的
    _hanlders.insert(ReqId::ID_GET_VARIFY_CODE,[this](const QJsonObject& jsonObj){
        qDebug() << "Processing verify code response:" << jsonObj; // 调试输出
        
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        
        QString email = jsonObj["email"].toString();
        showTip(tr("验证码已经发送"),true);
        qDebug() << "Email is:" << email;
    });
}
RegistDialog::~RegistDialog()
{
    delete ui;
}
