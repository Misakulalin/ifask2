#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"
using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;
class RPConPool {
public:
	RPConPool(size_t poolSize, std::string host, std::string port)
		: poolSize_(poolSize), host_(host), port_(port), b_stop_(false) {
		for (size_t i = 0; i < poolSize_; ++i) {

			std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port,
				grpc::InsecureChannelCredentials());

			connections_.push(VarifyService::NewStub(channel));
		}
	}

	~RPConPool() {
		std::lock_guard<std::mutex> lock(mutex_);
		Close();//通知线程回收资源
		while (!connections_.empty()) {
			connections_.pop();
		}
	}
	std::unique_ptr<VarifyService::Stub> getConnection() {//建立连接
		std::unique_lock<std::mutex> lock(mutex_);//unique_lock是一个互斥锁模板，功能是管理互斥锁
		cond_.wait(lock, [this] {
			if (b_stop_) {
				return true;
			}
			return !connections_.empty();//判断队列是否为空
			});
		//如果停止则直接返回空指针
		if (b_stop_) {
			return  nullptr;
		}
		auto context = std::move(connections_.front());
		connections_.pop();
		return context;
	}
	void returnConnection(std::unique_ptr<VarifyService::Stub> context) {//将连接线程放回线程池
		std::lock_guard<std::mutex> lock(mutex_);
		if (b_stop_) {
			return;
		}
		connections_.push(std::move(context));
		cond_.notify_one();
	}
	void Close() {
		b_stop_ = true;
		cond_.notify_all();
	}
private:
	std::atomic<bool> b_stop_;
	size_t poolSize_;
	std::string host_;
	std::string port_;
	std::queue<std::unique_ptr<VarifyService::Stub>> connections_;
	//使用唯一指针是因为在谷歌官方提供的接口使用的是智能指针
	std::mutex mutex_;
	std::condition_variable cond_;
};


class VerifyGrpcClient:public Singleton<VerifyGrpcClient>
{
	friend class Singleton<VerifyGrpcClient>;
public:
	~VerifyGrpcClient() {}//析构函数必须公开
	GetVarifyRsp GetVarifyCode(std::string email) {
		ClientContext context;
		GetVarifyRsp reply;
		GetVarifyReq request;
		request.set_email(email);
		//auto stub = pool_->getConnection();
		auto stub = pool_->getConnection();
		Status status = stub->GetVarifyCode(&context, request, &reply);

		if (status.ok()) {
			pool_->returnConnection(std::move(stub));//回收线程
			return reply;
		}
		else {
			pool_->returnConnection(std::move(stub));
			reply.set_error(ErrorCodes::RPCFailed);
			return reply;
		}
	}
private:
	VerifyGrpcClient();/*std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials());
		stub_ = VarifyService::NewStub(channel);*/
	std::unique_ptr<RPConPool> pool_;
	/*std::unique_ptr<VarifyService::Stub> stub_;*/
};
//class RPConPool {
//private:
//	void returnConnection(std::unique_ptr<VarifyService::Stub> context) {
//
//	}
//};

