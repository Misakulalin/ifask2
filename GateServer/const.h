#pragma once//���ܻ��ظ������ͷ�ļ�.
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
//CServer�๹�캯������һ���˿ںţ�����acceptor�����µ���������
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
