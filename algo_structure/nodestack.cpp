#include <cstddef>
#include <ctime>
#include <iostream>
#include <type_traits>
using namespace std;

// implemetn stack using nodes
// pop() push(), empty(), first in first out
// size()
// n <- n <- n <- n(front)

// type, t

class Lock{
// assume this is implemented as a standard mutex
public:
  void lock();
  void unlock();
};

template<typename T>
class Stack{
private:
  struct Node{
    T val;
    Node* next;
  };

  Lock lock;
  size_t length;
  Node* front;
public:

  Stack(): lock(Lock()),length(0),front(nullptr){};
  virtual ~Stack(){
    while (this->front) {
      this->pop();
    }
  }

  Node * top(){
    return this->front;
  }

  void push(const T &data);

  bool pop();

  size_t size() const{
    return this->length;
  };

  bool isEmpty() const{
    return this->front == nullptr;
  };

};

template<typename T>
void Stack<T>::push(const T & data){
  
  Node * node = new Node;
  lock.lock();
  Node * temp = this -> front;

  node -> val = data;
  node -> next = temp;

  this -> front = node;
  lock.unlock();
  this -> length ++;
}

template<typename T>
bool Stack<T> ::pop(){

  if(this ->isEmpty()){
    return false;
    
  }
  lock.lock();
  if (this->length == 1){
    delete this->front;
    this -> front = nullptr;
  }else {
    Node * temp = this->front;
    this -> front = this ->front->next;
    delete temp;  
  }
  lock.unlock();

  this -> length --;
  return false;
}



int main() {
  Stack<int> mystack;
  mystack.push(3);
  mystack.push(2);
  mystack.push(9);
  cout << mystack.size() << endl;

  
  cout << mystack.top()->val << endl;
  mystack.pop();
  mystack.pop();
  cout << mystack.top()->val << endl;

  return 0;
}

