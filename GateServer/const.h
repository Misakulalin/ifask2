#pragma once//可能会重复导入的头文件.
#include<iostream>
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include<memory>
#include "Singleton.h"
#include <functional>
#include <map>
#include <string>
#include <unordered_map>
//导入解析post请求的json库
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
//CServer类构造函数接受一个端口号，创建acceptor接受新到来的链接
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
//枚举类型，表示错误代码
enum ErrorCodes {
    Success = 0,
    Error_Json = 1001,  //Json解析错误
    RPCFailed = 1002,  //RPC请求错误
};
