#pragma once
#include "const.h"
class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;//定义处理方法使用的点在httpconnec。
class LogicSystem :public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>; 
public:
    ~LogicSystem()=default;
    bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
    void RegGet(std::string, HttpHandler handler);
    void RegPost(std::string url, HttpHandler handler);
    bool HandlePost(std::string path, std::shared_ptr < HttpConnection >con);
private:
    LogicSystem();
    std::map<std::string, HttpHandler> _post_handlers;
    std::map<std::string, HttpHandler> _get_handlers;
};

