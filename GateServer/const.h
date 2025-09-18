#pragma once//可能会重复导入的头文件.
#include<iostream>
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>//引入ptree对象
# include<boost/property_tree/ini_parser.hpp>//引入的方法是config对象的解析器
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
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "hiredis.h"//测试redis的头文件
#include <cassert>//测试redis封装方法的头文件
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
//class ConfigMgr;
//extern ConfigMgr gCfgMgr;在将验证服务变成多线程的时候，需要将这个变量注释