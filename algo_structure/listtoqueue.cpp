#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

// node, next, val;
template<typename T>
class Queue{
private:
    struct Node{
        T val;
        Node* next;
    };

    size_t length;
    Node* front; // head pointer
    Node* rear; // rear pointer

public:
// methods: Enqueue, dequeue, size(), empty()
    Queue():front(nullptr), rear(nullptr){
        this->length = 0;
    };

    virtual ~Queue(){
        while (this->front){
            this->pop();
        }
    }

    long size() const{
        // 如果把不改变数据成员的函数都加上const关键字进行标识，
        //显然，可提高程序的可读性。
        //其实，它还能提高程序的可靠性，
        //已定义成const的成员函数，一旦企图修改数据成员的值，则编译器按错误处理。 
        return this->length;
    }

    bool isEmpty()const {
        return (this->front == nullptr);
    }

    bool push(const T & data);
        //const引用是指向const对象的引用。
        //const引用必须被定义为const类型。

    bool pop();

    
};

template<typename T>
bool Queue<T>::push(const T & data){
    Node *node = new Node;
    node->val = data;
    node->next = nullptr;
    if (isEmpty()){
        this->front = node;
        this->rear = node;

    }else{
        this->rear->next = node;  //change the front
        this->rear = node;
    }

    this->length ++;
    return true;

}

template<typename T>
bool Queue<T> :: pop(){
    if(this->isEmpty()){
        return false;
    }

    if (this->front == this->rear){
        delete this->front;
        this->front = this->rear = nullptr;

    }else{
        Node* temp = this->front;
        this->front = this->front->next;
        delete temp;
    }

    this->length --;
    return false;


}

int main(){
    Queue<string> list;
    list.push("duck");
    list.push("fuck");
    list.push("hi");

    cout<<"list size is" << list.size()<< endl;
    list.pop();
    list.pop();
    cout << list.size()<< endl;
    return 0;

}
