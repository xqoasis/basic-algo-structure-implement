#include<iostream>

using namespace std;

class A{
public:
    int i;
    A():i(10){};
};

class B : public A{
public:
    int j;
    B():j(20){};
};

int main(){
    B b;
    B* p = &b;
    A* pl = &b; // 如果没有B继承A，这一条失败, 说明pl指的东西在cpp判定中也是个A类型的obj
    A &ptr = b; // 引用
    cout << p->i <<endl;
    cout << ptr.i << endl;



}