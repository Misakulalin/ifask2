#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include "global.h"
#include <QJsonObject>
#include<QNetworkReply>
#include <QJsonDocument>
class HttpMgr :public QObject, public singleton<HttpMgr>
    , public std::enable_shared_from_this<HttpMgr>
{
     Q_OBJECT//宏定义，声明之后可以使用信号和槽机制，动态属性系统等
public:
      ~HttpMgr();
private:
    friend class singleton<HttpMgr>;//作为单例类的友元函数
    HttpMgr();

    QNetworkAccessManager _manager;//一个网络对象
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private slots://槽函数的声明
    void  slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);//第一个信号定义信号,发出什么信号
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);//引用

};

#endif // HTTPMGR_H
