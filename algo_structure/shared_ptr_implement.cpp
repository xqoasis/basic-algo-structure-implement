#include <iostream>
#include <mutex>
#include <thread>
// shared_ptr的原理：是通过引用计数的方式来实现多个shared_ptr对象之间共享资源。

// shared_ptr在其内部，给每个资源都维护了着一份计数，用来记录该份资源被几个对象共享。
// 在对象被销毁时(也就是析构函数调用)，就说明自己不使用该资源了，对象的引用计数减一。
// 如果引用计数是0，就说明自己是最后一个使用该资源的对象，必须释放该资源；
// 如果不是0，就说明除了自己还有其他对象在使用该份资源，不能释放该资源，否则其他对象就成野指针了。
using namespace std;

template<class T>
class Shared_ptr_implement
{
private:
    int *_pRefCount;
    T* _pPtr;
    mutex* _pMutex;
private:
    void Release() {
        bool deleteFlag = false;
        _pMutex -> lock(); // about to sub
        if (--(*_pRefCount) == 0) {
            // release the resource
            delete _pRefCount;
            delete _pPtr;
            deleteFlag = true;
        }
        _pMutex -> unlock();
        if (deleteFlag == true) delete _pMutex;
    }
public:
    Shared_ptr_implement(T* ptr = nullptr)
        :_pPtr(ptr)
        , _pRefCount(new int(1)) 
        , _pMutex(new mutex)
    {}

    ~Shared_ptr_implement()
    {
        Release();
    }
    // 拷贝构造
    Shared_ptr_implement(const Shared_ptr_implement<T> &sp)
        :_pPtr(sp._pPtr)
        ,_pRefCount(sp._pRefCount)
        ,_pMutex(sp._pMutex)
    {
        AddRefCount();
    }
    // 赋值操作: sp=sp2
    Shared_ptr_implement<T>& operator=(const Shared_ptr_implement<T>& sp) {
        if(sp._pPtr != _pPtr) {
            Release();
            _pPtr = sp._pPtr;
            _pRefCount = sp._pRefCount;
            _pMutex = sp._pMutex;
            AddRefCount();
        }
        return *this;
    }
    T& operator*(){
        return *_pPtr;
    }
    T& operator->(){
        return _pPtr;
    }


    // 操作符


    int UseCount() {
        return *_pRefCount;
    }

    T* Get() {
        return _pPtr;
    }

    void AddRefCount() {
        _pMutex -> lock();
        ++(*_pRefCount);
        _pMutex -> unlock();
    }
};



// 成员变量或者私有成员变量的前面加上下划线。以表示该变量是某个类的属性。





// 创建一个int型数，并且用()括号中的数据进行初始化,例如：
//int *p = new int(10); // p指向一个值为10的int数。