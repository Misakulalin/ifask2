#pragma once
#include"HttpConnection.h"
#include<iostream>
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
//CServer类构造函数接受一个端口号，创建acceptor接受新到来的链接
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using namespace std;
class CServer :public std::enable_shared_from_this<CServer>
{
public:
    //允许访问共享指针么
	CServer(boost::asio::io_context& ioc, unsigned short& port);//构造函数，port代表端口号，io_conntext是io上下文对象可以实现异步操作
    //的管理以及多个 I/O 对象的共享。可以在多个线程中运行，以并发处理 I/O 事件。将它作为引用传递，
    // 使得在应用程序级别统一配置和管理线程池变得更加容易。根据 TCP/IP 协议的规定（如 RFC 793），端口号是一个 16 位的无符号整数
    void Start();//监听新链接
private:
	tcp::acceptor  _acceptor;//tcp中的acceptor类，用于接受新到来的链接
	net::io_context& _ioc;//net::io_context 是 Boost.Asio 中的一个核心类，用于管理异步 I/O 操作和事件循环。
	boost::asio::ip::tcp::socket   _socket;//网络套接字，用于与客户端进行通信。
};

