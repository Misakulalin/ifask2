#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include "global.h"
#include <memory>
#include <QJsonObject>
#include <QJsonDocument>
class HttpMgr :public QObject, public singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr>
{
     Q_OBJECT
public:
    HttpMgr();
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);//需要发送的信号

private:
    friend class singleton<HttpMgr>;
    HttpMgr();
    void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)；
    QNetworkAccessManager _manager;
signals:
    void sig_http_finish();
};

#endif // HTTPMGR_H
