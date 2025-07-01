#ifndef SINGLETON_H
#define SINGLETON_H //单例类
#include <memory>
#include <mutex>//用来实现多线程
#include <iostream>//c++标准库

using namespace std;
//singleton《T》是一种类型
template <typename T>//使用模板，T只是模板在实际的使用中需要用具体的类名来代替
class singleton {
protected:
    singleton() = default;//定义默认构造函数
    singleton(const singleton<T>&) = delete;//禁止拷贝函数
    singleton& operator=(const singleton<T>& st) = delete;//禁止拷贝赋值函数，operate用来重新定义C++中已有运算符的行为在这里等于就相当于赋值
    ~singleton() {
        std::cout << "this is singleton destruct" << std::endl;//析构函数，也就是上面的protected就是一部分构造函数
    }

    static std::shared_ptr<T> _instance;//创建一个静态的共享指针，static 成员变量的生命周期与整个程序的生命周期相同。它在程序启动时被创建，在程序结束时被销毁。它不依赖于任何对象的创建或销毁。
//对于外界来说，这个共享指针是不可见的，而要访问这个指针就只能通过get方法来进行。
public:
    static std::shared_ptr<T> GetInstance() {//返回值是共享指针的get函数，作用是
        static std::once_flag s_flag;//初始化一个对象。确保某个函数（或代码块）在多线程环境下，无论多少个线程同时尝试调用它，都只会被成功执行一次。
        std::call_once(s_flag, [&]() {//s_flag代表着一个只会被执行一次的状态。在进入的时候会检查s_flag的状态，如果是未调用，就执行该函数并且把这个状态转换成已执行。之后再调用就不给执行了。
            _instance = shared_ptr<T>(new T);//只允许执行一次的功能是创建一个共享指针。
        });
        return _instance;
    }

    void PrintAddress() {//获取创建的共享指针
        if (_instance) {
            std::cout << _instance.get() << endl;
        } else {
            std::cout << "Instance not created yet" << endl;
        }
    }
};

template <typename T>//在模板类的定义之外来定义类中间的函数，必须要在后面也定义上模板
std::shared_ptr<T> singleton<T>::_instance = nullptr;//初始化在类中声明的指针

#endif // SINGLETON_H
