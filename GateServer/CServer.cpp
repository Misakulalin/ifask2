#include "CServer.h"
CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) :_ioc(ioc), //构造函数初始化成员变量
_acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _socket(ioc) {
}//列表初始化完成，_acceptor将绑定到指定的端口上，_socket将用于与客户端进行通信。

void CServer::Start()
{
	auto self = shared_from_this();//将共享指针传递给lambda表达式，以便在异步操作完成后仍然可以访问CServer对象。
    _acceptor.async_accept(_socket, [self](beast::error_code ec) {//接受socker然后返回消息。
        try {//异常处理
            //出错则放弃这个连接，继续监听新链接
			if (ec) {//ec是错误码，如果有错误发生，则会被设置为非零值。
                self->Start();
                return;
            }
            //处理新链接，创建HpptConnection类管理新连接
            std::make_shared<HttpConnection>(std::move(self->_socket))->Start();//创造的链接时需要复用的，所以使用move将创建的socker
			//套接字给传给hettp。为什么不使用引用呢？使用引用的时候会有新的链接进入，原来的链接会被覆盖掉，
            //继续监听，将_socket内部数据转移给HttpConnection管理，_socket继续用来接受写的链接。
			self->Start();//继续监听新的连接请求
        }
        catch (std::exception& exp) {//抛出异常的常用类
            std::cout << "exception is " << exp.what() << std::endl;//描述异常。
            self->Start();
        }
        });
}
