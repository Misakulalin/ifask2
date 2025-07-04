#pragma once
#include"const.h"//���ñ��ؿ�

class HttpConnection: public std::enable_shared_from_this<HttpConnection>//�̳й���ָ��
{
	friend class LogicSystem;//һ���������Ԫ��
public:
	HttpConnection(tcp::socket socket);//CSver�д����socker�׽���
	void Start();//Start() ��������ͨ����ֱ��ʵ�ֺ��Ĺ��ܣ�������Ϊ��������Э�������������������Ĺ��ܡ��������ﲻһ����
private:
    void CheckDeadline();//��ʱ���
	void WriteResponse();//�յ����Ӳ��Ҵ����������д��Ӧ��
    void HandleReq();//��������
    tcp::socket  _socket;//һ��socker
    // �ֽ�����
    beast::flat_buffer  _buffer{ 8192 };//���캯���Ĳ������ݣ��������Ĳ����Ƕ��١�

    // ���ܸ�������
    http::request<http::dynamic_body> _request;

	//�ظ���Ӧ��dynamic_body ������Ӧ��Ĵ�С������ʱ��̬�仯��
    http::response<http::dynamic_body> _response;

    // ��������ʱ���ж������Ƿ�ʱ
    net::steady_timer deadline_{
		_socket.get_executor(), std::chrono::seconds(60) };//get_executor() ��ȡִ������steady_timer ��������һ����ʱ����std::chrono::seconds(60) ���ó�ʱʱ��Ϊ60��
    //ִ�����Ƕ��첽�¼����й���ģ����Լ�ʱ����Ҫ��ִ������ȥ��ȡ��ʱ�Ŀ�ʼ�ڵ㡣
};

