#ifndef GLOBAL_H//一个声明全局变量的类，方便管理
#define GLOBAL_H
#include <QWidget>
#include <functional>//function函数
#include "QStyle"
#include<QByteArray>
extern std::function<void(QWidget*)> repolish;//extern声明这是一个全局变量
enum ReqId{//请求的id
    ID_GET_VARIFY_CODE = 1001, //获取验证码
    ID_REG_USER = 1002, //注册用户
};
enum ErrorCodes{ //错误代码
    SUCCESS = 0,
    ERR_JSON = 1, //Json解析失败
    ERR_NETWORK = 2,
    };
enum Modules{//模块
    REGISTERMOD = 0,
    };

class global
{
public:
    global();

};

#endif // GLOBAL_H
