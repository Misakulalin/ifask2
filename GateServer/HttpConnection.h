#pragma once
#include"const.h"//引用本地库

class HttpConnection: public std::enable_shared_from_this<HttpConnection>//继承共享指针
{
	friend class LogicSystem;//一个信类的友元类
public:
	HttpConnection(tcp::socket socket);//CSver中传入的socker套接字
	void Start();//Start() 方法本身通常不直接实现核心功能，而是作为调度器或协调器来调用其他函数的功能。但在这里不一样。
private:
    void CheckDeadline();//超时检测
	void WriteResponse();//收到链接并且处理完请求后，写入应答。
    void HandleReq();//处理请求
    tcp::socket  _socket;//一个socker
    // 字节数组
    beast::flat_buffer  _buffer{ 8192 };//构造函数的参数传递，缓冲区的参数是多少。

    // 接受各种请求
    http::request<http::dynamic_body> _request;

	//回复响应，dynamic_body 允许响应体的大小在运行时动态变化。
    http::response<http::dynamic_body> _response;

    // 用来做定时器判断请求是否超时
    net::steady_timer deadline_{
		_socket.get_executor(), std::chrono::seconds(60) };//get_executor() 获取执行器，steady_timer 用于设置一个定时器，std::chrono::seconds(60) 设置超时时间为60秒
    //执行器是对异步事件进行管理的，所以计时器需要从执行器中去获取计时的开始节点。
};

