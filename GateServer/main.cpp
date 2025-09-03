#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "CServer.h"
#include "ConfigMgr.h"//包含的是配置文件的读取逻辑
int main()
{
    ConfigMgr gCfgMgr;
    std::string gate_port_str = gCfgMgr["GateServer"]["Port"];
    unsigned short gate_port = atoi(gate_port_str.c_str());
    try
    {
        unsigned short port = static_cast<unsigned short>(8080);//端口一般是无符号的
		net::io_context ioc{ 1 };//初始化io_context对象，参数1表示线程数为1
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);//asio网络库
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
