#include "HttpConnection.h"
#include "LogicSystem.h"

HttpConnection::HttpConnection(tcp::socket socket) : _socket(std::move(socket))//列表初始化,SCver类传入的socker套接字
{ }
void HttpConnection::Start()
{
	auto self = shared_from_this(); //获取当前对象的共享指针
    http::async_read(_socket, _buffer, _request, [self](beast::error_code ec, std::size_t bytes_transferred) {

        try {
            if (ec) {
				std::cout << "Error reading request: " << ec.what() << std::endl;
            }
            boost::ignore_unused(bytes_transferred);
            self->HandleReq();//处理请求
			self->CheckDeadline(); //检查超时

        }catch(std::exception& exp){
            std::cout << "exception is " << exp.what() << std::endl;//C++ 标准库中，几乎所有标准异常都继承自 std::exception
        }
        });
    
    /*异步调用HTTP,这是http类的async方法所需要的参数
    async_read(
        AsyncReadStream & stream,数据流
        DynamicBuffer & buffer, 字节大小
        basic_parser<isRequest>&parser, 请求参数，我们一般也要传递能接受多种资源类型的请求参数。
        ReadHandler && handler)回调函数，接受成功或者失败，都会触发回调函数*/
}
void HttpConnection::HandleReq() {
    //设置版本
    _response.version(_request.version());
    //设置为短链接
    _response.keep_alive(false);

    if (_request.method() == http::verb::get) {
        bool success = LogicSystem::GetInstance()->HandleGet(_request.target(), shared_from_this());
        if (!success) {
            _response.result(http::status::not_found);
            _response.set(http::field::content_type, "text/plain");
            beast::ostream(_response.body()) << "url not found\r\n";
            WriteResponse();
            return;
        }

        _response.result(http::status::ok);
        _response.set(http::field::server, "GateServer");
        WriteResponse();
        return;
    }
}

void HttpConnection::WriteResponse() {
    //异步写入响应
	auto self = shared_from_this();//延长生命周期防止被释放掉
    _response.content_length(_response.body().size());//传入body的长度
    http::async_write(_socket, _response,
        [self](beast::error_code ec, std::size_t){
            self->_socket.shutdown(tcp::socket::shutdown_send, ec);
            self->deadline_.cancel();
        }
        );
}
void HttpConnection::CheckDeadline() {
    auto self = shared_from_this();

    deadline_.async_wait(
        [self](beast::error_code ec)
        {
            if (!ec)
            {
                // Close socket to cancel any outstanding operation.
                self->_socket.close(ec);
            }
        });
}