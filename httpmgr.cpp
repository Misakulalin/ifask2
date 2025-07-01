#include "httpmgr.h"

HttpMgr::~HttpMgr(){
}

HttpMgr::HttpMgr(){
    connect(this,&HttpMgr::sig_http_finish,this,&HttpMgr::slot_http_finish);//检测到发射完毕后的槽函数
}
void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)//发送请求，传入的参数是url,json错误代码和模块
    {
        QByteArray data = QJsonDocument(json).toJson(); //QByteArray 是 Qt 用来存储原始字节序列的类，非常适合用于网络传输或文件读写。
        QNetworkRequest request(url);//通过url构造请求，包含我们即将发送的 HTTP 请求
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");//设置请求头，请求头是map形式。ContentTypeHeader是一个枚举值
        //QNetworkRequest 类内部预先定义了很多常用的 HTTP 头部字段作为枚举成员。ContentTypeHeader是枚举类的一个成员，一个常量。接下来要发送给你的数据主体（body）是 JSON 格式
        //设置HTTP 头部信息。ContentTypeHeader是指请求头格式，后面跟的是具体的格式，所以请求头是1：1格式的。
        request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
        //请求头数据主体的长度。
        //发送请求，并处理响应, 获取自己的智能指针，构造伪闭包并增加智能指针引用计数
        auto self = shared_from_this();//post方法是QNetworkAccessManager类中用来发起 HTTP POST 请求的核心方法。
        QNetworkReply * reply = _manager.post(request, data);//头文件中定义的一个对象，reply是它的指针。post请求的参数是url和data.
            //设置信号和槽等待发送完成
        QObject::connect(reply,&QNetworkReply::finished,[self,reply,req_id,mod](){//lambda捕获局部参数
            if(reply->error()!=QNetworkReply::NoError){//如果出现错误
                qDebug()<<reply->errorString();

                //发送信号
                emit self->sig_http_finish(req_id,"",ErrorCodes::ERR_NETWORK,mod);
                reply->deleteLater();
                return;
            }
           //如果没有错误
            QString res=reply->readAll();//读取请求
            emit self->sig_http_finish(req_id,res,ErrorCodes::SUCCESS,mod) ;//发射完毕的信号
            reply->deleteLater();//回复
            return;
        });//信号和槽的连接函数.发出信号的源头是reply,发射的信号是finished，作用的主体是reply，self,rpd

    }
  void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod){//
      if(mod==Modules::REGISTERMOD){
          //发送信号
          emit sig_reg_mod_finish(id,res,err);//准备完毕发射信号
      }
}
