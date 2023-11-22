#include<iostream>
using namespace std;

class father
{
private:
    int money;
public:
    virtual void getMoney(){
        cout << "father money" << endl;
    };
    // //如果没有virtual进行动态鄉定，那么在后期输入只能输出father部分，用指针和地址输出不了son部分
    //static binding，static binding function is based on the type of pointer to the object，a's type is FATHER， we get the father's function -- fetMoney
    //To implement different outputs use virtual virtual functions

    //It is possible to achieve runtime polymorphism without inheritance relationships, 
    // where the function names of two different classes need to be added to virtual in order to work,
    // and where the defined pointers to other objects are subject to forced conversions

    


};

class son_0:public father
{
private:
    int money;
public:
    void getMoney(){
        cout << "son0 getmoney" << endl;
    }

};

class son_1:public father
{
private:
    int money;
public:
    void getMoney(){
        cout << "son1 getmoney" << endl;
    }

};

int main(){
    father *a;
    son_1 b;
    a = &b; // 如果不使用virtual进行动态鄉定，那么在后面使用a的getMoney的时候出来的是father类的getMoney function，is not son's b obj's getMoney function
    a -> getMoney(); 



    return 0;
}