#pragma once
#include"HttpConnection.h"
#include<iostream>
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
//CServer�๹�캯������һ���˿ںţ�����acceptor�����µ���������
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using namespace std;
class CServer :public std::enable_shared_from_this<CServer>
{
public:
    //������ʹ���ָ��ô
	CServer(boost::asio::io_context& ioc, unsigned short& port);//���캯����port����˿ںţ�io_conntext��io�����Ķ������ʵ���첽����
    //�Ĺ����Լ���� I/O ����Ĺ��������ڶ���߳������У��Բ������� I/O �¼���������Ϊ���ô��ݣ�
    // ʹ����Ӧ�ó��򼶱�ͳһ���ú͹����̳߳ر�ø������ס����� TCP/IP Э��Ĺ涨���� RFC 793�����˿ں���һ�� 16 λ���޷�������
    void Start();//����������
private:
	tcp::acceptor  _acceptor;//tcp�е�acceptor�࣬���ڽ����µ���������
	net::io_context& _ioc;//net::io_context �� Boost.Asio �е�һ�������࣬���ڹ����첽 I/O �������¼�ѭ����
	boost::asio::ip::tcp::socket   _socket;//�����׽��֣�������ͻ��˽���ͨ�š�
};

