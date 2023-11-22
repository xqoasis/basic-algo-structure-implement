#include <iostream>
using namespace std;


template<typename T>
class bst{
private:
    struct Node{
        T data;
        Node *left;
        Node *right;
    };
    Node *root;

public:
    bst():root(nullptr){};

    bool isempty() const{
        return (root == nullptr);
    }

    void insert(const T & val);
};


template<typename T>
void bst<T>::insert(const T &val){
    Node *node = new Node;
    Node *parent;
    node ->data = val;
    node ->left = nullptr;
    node ->right =  nullptr;
    parent = nullptr;
    if (isempty()){
        root = node;
    }else{
        Node *ptr = root;
        while (ptr != nullptr){
            parent = ptr;
            if (val > parent->data){
                parent = parent->right;
            }else{
                parent = parent -> left;
            }
        }
        if (val >= parent->data){
            parent ->right = node;
        }else{
            parent -> left = node;
        }
    }

}

int main(){
    bst<int> b;
    b.insert(20);
    b.insert(10);
    b.insert(5);
    b.insert(15);
    b.insert(40);
    b.insert(45);
    b.insert(30); 

    return 0;
}