#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "CServer.h"
int main()
{
    try
    {
        unsigned short port = static_cast<unsigned short>(8080);//�˿�һ�����޷��ŵ�
		net::io_context ioc{ 1 };//��ʼ��io_context���󣬲���1��ʾ�߳���Ϊ1
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);//asio�����
        signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {

            if (error) {
                return;
            }
            ioc.stop();
            });
        std::make_shared<CServer>(ioc, port)->Start();
        ioc.run();
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
