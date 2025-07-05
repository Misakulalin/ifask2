#include "HttpConnection.h"
#include "LogicSystem.h"

HttpConnection::HttpConnection(tcp::socket socket) : _socket(std::move(socket))//�б��ʼ��,SCver�ഫ���socker�׽���
{ }
void HttpConnection::Start()
{
	auto self = shared_from_this(); //��ȡ��ǰ����Ĺ���ָ��
    http::async_read(_socket, _buffer, _request, [self](beast::error_code ec, std::size_t bytes_transferred) {

        try {
            if (ec) {
				std::cout << "Error reading request: " << ec.what() << std::endl;
            }
            boost::ignore_unused(bytes_transferred);//�������������ƹ���
            self->HandleReq();//��������
			self->CheckDeadline(); //��鳬ʱ

        }catch(std::exception& exp){
            std::cout << "exception is " << exp.what() << std::endl;//C++ ��׼���У��������б�׼�쳣���̳��� std::exception
        }
        });
    
    /*�첽����HTTP,����http���async��������Ҫ�Ĳ���
    async_read(
        AsyncReadStream & stream,������
        DynamicBuffer & buffer, �ֽڴ�С
        basic_parser<isRequest>&parser, �������������һ��ҲҪ�����ܽ��ܶ�����Դ���͵����������
        ReadHandler && handler)�ص����������ܳɹ�����ʧ�ܣ����ᴥ���ص�����*/
}
void HttpConnection::HandleReq() {
    //���ð汾
    _response.version(_request.version());
    //����Ϊ������
    _response.keep_alive(false);

    if (_request.method() == http::verb::get) {
        PreParseGetParam();
        bool success = LogicSystem::GetInstance()->HandleGet(_get_url, shared_from_this());//���������������
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
    //�첽д����Ӧ
	auto self = shared_from_this();//�ӳ��������ڷ�ֹ���ͷŵ�
    _response.content_length(_response.body().size());//����body�ĳ���
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

//char תΪ16���ƣ�URL �淶��RFC 3986���涨ʹ��ʮ�����ơ�
unsigned char ToHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}
//16����תʮ���Ƶ�char
unsigned char FromHex(unsigned char x)
{
    unsigned char y;
    if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') y = x - '0';
    else assert(0);//assert() �� C++ ��׼���е�һ���꣬���Ƿ��������ڵ���ʱ�Ķ��Լ�顣
    return y;
}
//���룬URL ֻ�ܰ���ASCII �ַ�����ĸ�����֡����ַ��ţ���
std::string UrlEncode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        //�ж��Ƿ�������ֺ���ĸ���ɣ������ַ������ʾΪ %XX ��ʽ��
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ') //Ϊ���ַ�
            strTemp += "+";
        else
        {
            //�����ַ���Ҫ��ǰ��%���Ҹ���λ�͵���λ�ֱ�תΪ16����
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);//����λ��һ���ֽڵ�ǰ4λ�����4λ��������λ�෴��
            strTemp += ToHex((unsigned char)str[i] & 0x0F);//һ���ֽڸպ�������ʮ���������֡�
        }
    }
    return strTemp;
}
//����
std::string UrlDecode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        //��ԭ+Ϊ��
        if (str[i] == '+') strTemp += ' ';
        //����%������������ַ���16����תΪchar��ƴ��
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char)str[++i]);//++i ��������ʹ�ã�iָ����һ���ַ�
            unsigned char low = FromHex((unsigned char)str[++i]);
            strTemp += high * 16 + low;
        }
        else strTemp += str[i];//λ��Ȩֵ�� 16����λ��Ȩֵ�� 1�� ��Ϲ�ʽ��value = high * 16 + low��
       
    }
    return strTemp;
}
void HttpConnection::PreParseGetParam() {

    // ��ȡ URI  
    auto uri = _request.target(); 
    auto query_pos = uri.find('?');
    if (query_pos == std::string::npos) {
        _get_url = uri;
        return;
    }
    _get_url = uri.substr(0, query_pos);//��ȡ ? ֮ǰ�Ĳ�����Ϊ·��
    std::string query_string = uri.substr(query_pos + 1);
    std::string key;
    std::string value;
    size_t pos = 0;//׼��������ѯ�����ַ����еļ�ֵ��
    //ÿ���ҵ�һ�� &������Ϊǰ����һ�������,�ڲ������в��� = �ָ� key �� value��
    while ((pos = query_string.find('&')) != std::string::npos) {
        auto pair = query_string.substr(0, pos);
        size_t eq_pos = pair.find('=');//size_t��ʾ�޷����������͡�
        if (eq_pos != std::string::npos) {
            key = UrlDecode(pair.substr(0, eq_pos)); // ������ url_decode ����������URL���� ,���������� key �� value ���� ��
            value = UrlDecode(pair.substr(eq_pos + 1));
            _get_params[key] = value;
        }
        query_string.erase(0, pos + 1);
    }
    // �������һ�������ԣ����û�� & �ָ�����  
    if (!query_string.empty()) {
        size_t eq_pos = query_string.find('=');
        if (eq_pos != std::string::npos) {
            key = UrlDecode(query_string.substr(0, eq_pos));
            value = UrlDecode(query_string.substr(eq_pos + 1));
            _get_params[key] = value;
        }
    }
}