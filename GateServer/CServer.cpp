#include "CServer.h"
CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) :_ioc(ioc), //���캯����ʼ����Ա����
_acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _socket(ioc) {
}//�б��ʼ����ɣ�_acceptor���󶨵�ָ���Ķ˿��ϣ�_socket��������ͻ��˽���ͨ�š�

void CServer::Start()
{
	auto self = shared_from_this();//������ָ�봫�ݸ�lambda���ʽ���Ա����첽������ɺ���Ȼ���Է���CServer����
    _acceptor.async_accept(_socket, [self](beast::error_code ec) {//����sockerȻ�󷵻���Ϣ��
        try {//�쳣����
            //���������������ӣ���������������
			if (ec) {//ec�Ǵ����룬����д���������ᱻ����Ϊ����ֵ��
                self->Start();
                return;
            }
            //���������ӣ�����HpptConnection�����������
            std::make_shared<HttpConnection>(std::move(self->_socket))->Start();//���������ʱ��Ҫ���õģ�����ʹ��move��������socker
			//�׽��ָ�����hettp��Ϊʲô��ʹ�������أ�ʹ�����õ�ʱ������µ����ӽ��룬ԭ�������ӻᱻ���ǵ���
            //������������_socket�ڲ�����ת�Ƹ�HttpConnection����_socket������������д�����ӡ�
			self->Start();//���������µ���������
        }
        catch (std::exception& exp) {//�׳��쳣�ĳ�����
            std::cout << "exception is " << exp.what() << std::endl;//�����쳣��
            self->Start();
        }
        });
}
