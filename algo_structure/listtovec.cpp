#include<iostream>
#include<string>

//specify type? template
//max length? no
//max input length?

//顺序,isam,
//function:
// push_back, size, index, pop_back, clear
// erase

//indexed access method -- 1 pointer, rear
//size related pushback, 

using namespace std;
// template<typename T>与template<class T>
//一般情况下这两个通用，但有一个特例，就是当 T 是一个类，
//而这个类又有子类(假设名为 innerClass) 时，
//应该用 template<typename>:

template<class T>
class Myvector{
public:

    //member fucntion
    Myvector();
    Myvector(size_t n, const T& val);

    //iterator begin();
    //iterator end();
    //const_iterator begin();
    //const_iterator end();
    size_t capacity()const;
    size_t size()const;
    void reserve(size_t n);
    bool empty()const;

    void push_back(const T & x);
    void pop_back();
    
    T& operator[](size_t i);//brackets, 
    const T& operator[](size_t i)const;


private:
    T* _start;
    T* _finish;
    T* _endofstorage;


    // size_t capacity;
    //bool resize(size_t newcapacity);
};

template<typename T>
Myvector<T>:: Myvector()
                        :_start(nullptr)
                        ,_finish(nullptr)
                        ,_endofstorage(nullptr)
{};

template<typename T>
Myvector<T>:: Myvector(size_t n, const T& val)
                        :_start(nullptr)
                        ,_finish(nullptr)
                        ,_endofstorage(nullptr)
{
    reserve(n);
    while (n --){
        push_back(val);
    }
};
template<typename T>
size_t Myvector<T> :: capacity()const
{
    return _endofstorage - _start;
}
template<typename T>
size_t Myvector<T>::size() const
{
    return _finish - _start;
}

template<typename T>
void Myvector<T>::push_back(const T& value)
{
    if(_finish == _endofstorage){
        size_t newC = _endofstorage == nullptr?1:2*capacity();
        reverse(value);
    }

    *_finish = value;
    ++_finish;
}
template<typename T>
void Myvector<T> :: reserve(size_t n)
{
    if (n > capacity()){
        size_t sz = size();
        T*arr = new T[n];
        if (_start)
        {
            memcpy(arr, _start, sizeof(T)*sz);
            delete[] _start;
        }
        //update
        _start = arr;
        _finish = _start + sz;
        _endofstorage = _start + n;
    }
}













