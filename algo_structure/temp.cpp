#include <iostream>
using namespace std;
template<class T> class Node { 
public:
    T value;
    Node<T>* next;
    Node<T>* prev;

public:
    Node(T v) : value(v), next(nullptr), prev(nullptr) {}
};

template<class T> class LinkedList {
private:
    /**
    * stores the first Node in "dummy->next", * and the last Node in "dummy->prev". */
    Node<T>* dummy;

public:
    LinkedList<T>() : dummy(new Node<T>(T())) {}

    T Head() const { return dummy->next->value; } 
    T Last() const { return dummy->prev->value; }
    void pushFront(T v) {
        Node<T>* newNode = new Node<T> (v);
        newNode -> next = dummy -> next;
        newNode -> prev = dummy;
        if (dummy -> next != nullptr) {
            dummy -> next -> prev = newNode;
        }
        dummy -> next = newNode;
        if (dummy->prev == nullptr) {
            dummy->prev = newNode;
        }
    }

    void pushBack(T v) {
        Node<T>* newNode = new Node<T> (v);
        newNode -> next = dummy;
        newNode -> prev = dummy -> prev;

        if (dummy -> prev != nullptr) {
            dummy -> prev -> next = newNode;
        }
        dummy -> prev = newNode;
        if (dummy->next == nullptr) {
            dummy->next = newNode;
        }
    }

    int Size() const {
        int size = 0;
        Node<T>* current = dummy -> next;
        while (current != dummy)
        {
            cout << current -> value << " ";
            size ++;
            current = current -> next;
        }
        return size;
        
    }
};

// Test:
int main() {
    LinkedList<int> linkedList;

    // Add elements to the front of the list
    linkedList.pushFront(3);
    linkedList.pushFront(2);
    linkedList.pushFront(1);


    cout << linkedList.Head() << " ";
    cout << linkedList.Size() << " ";

    linkedList.pushBack(4);
    linkedList.pushBack(5);

    cout << linkedList.Size() << " ";

    return 0;
}