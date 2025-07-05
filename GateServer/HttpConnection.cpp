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
            boost::ignore_unused(bytes_transferred);//编译器警告抑制工具
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
        PreParseGetParam();
        bool success = LogicSystem::GetInstance()->HandleGet(_get_url, shared_from_this());//传入带参数的链接
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
    if (_request.method() == http::verb::post) {
        bool success = LogicSystem::GetInstance()->HandlePost(_request.target(), shared_from_this());
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
     
                self->_socket.close(ec);
            }
        });
}

//char 转为16进制，URL 规范（RFC 3986）规定使用十六进制。
unsigned char ToHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}
//16进制转十进制的char
unsigned char FromHex(unsigned char x)
{
    unsigned char y;
    if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') y = x - '0';
    else assert(0);//assert() 是 C++ 标准库中的一个宏，不是方法，用于调试时的断言检查。
    return y;
}
//编码，URL 只能包含ASCII 字符（字母、数字、部分符号）。
std::string UrlEncode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        //判断是否仅有数字和字母构成，特殊字符必须表示为 %XX 格式。
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ') //为空字符
            strTemp += "+";
        else
        {
            //其他字符需要提前加%并且高四位和低四位分别转为16进制
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);//高四位：一个字节的前4位（左边4位），低四位相反。
            strTemp += ToHex((unsigned char)str[i] & 0x0F);//一个字节刚好是两个十六进制数字。
        }
    }
    return strTemp;
}
//解码
std::string UrlDecode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        //还原+为空
        if (str[i] == '+') strTemp += ' ';
        //遇到%将后面的两个字符从16进制转为char再拼接
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char)str[++i]);//++i 先自增再使用，i指向下一个字符
            unsigned char low = FromHex((unsigned char)str[++i]);
            strTemp += high * 16 + low;
        }
        else strTemp += str[i];//位的权值是 16，低位的权值是 1， 组合公式：value = high * 16 + low。
       
    }
    return strTemp;
}
void HttpConnection::PreParseGetParam() {

    // 提取 URI  
    auto uri = _request.target(); 
    auto query_pos = uri.find('?');
    if (query_pos == std::string::npos) {
        _get_url = uri;
        return;
    }
    _get_url = uri.substr(0, query_pos);//提取 ? 之前的部分作为路径
    std::string query_string = uri.substr(query_pos + 1);
    std::string key;
    std::string value;
    size_t pos = 0;//准备解析查询参数字符串中的键值对
    //每次找到一个 &，就认为前面是一组参数对,在参数对中查找 = 分割 key 和 value。
    while ((pos = query_string.find('&')) != std::string::npos) {
        auto pair = query_string.substr(0, pos);
        size_t eq_pos = pair.find('=');//size_t表示无符号整数类型。
        if (eq_pos != std::string::npos) {
            key = UrlDecode(pair.substr(0, eq_pos)); // 假设有 url_decode 函数来处理URL解码 ,将解析出的 key 和 value 存入 。
            value = UrlDecode(pair.substr(eq_pos + 1));
            _get_params[key] = value;
        }
        query_string.erase(0, pos + 1);
    }
    // 处理最后一个参数对（如果没有 & 分隔符）  
    if (!query_string.empty()) {
        size_t eq_pos = query_string.find('=');
        if (eq_pos != std::string::npos) {
            key = UrlDecode(query_string.substr(0, eq_pos));
            value = UrlDecode(query_string.substr(eq_pos + 1));
            _get_params[key] = value;
        }
    }
}