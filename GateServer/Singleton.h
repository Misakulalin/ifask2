#pragma once//单例类模式
#include <memory>
#include <mutex>
#include <iostream>
template <typename T>
class Singleton {
protected:
    Singleton() = default;//初始化为默认值
    Singleton(const Singleton<T>&) = delete;//禁止拷贝
    Singleton& operator=(const Singleton<T>& st) = delete;//禁止赋值

    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            _instance = std::shared_ptr<T>(new T);
            });

        return _instance;
    }
    void PrintAddress() {
        std::cout << _instance.get() << std::endl;
    }
    ~Singleton() {
        std::cout << "this is singleton destruct" << std::endl;
    }
};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;
