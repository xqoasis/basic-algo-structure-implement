#include <iostream>
#include <vector>
#include <stdio.h>
#include <unordered_map>

using namespace std;

class Node{
public:
    int key, val;
    Node * next;
    Node * pre;
    Node(int k, int v):key(k), val(v){};
};

// make it is int
class DoubleList{
private:
    Node * head;
    Node * tail;
    size_t length;
public:
    DoubleList():head(new Node(0, 0)), tail(new Node(0, 0)), length(0){
        head ->next = tail;
        tail -> pre = head;
        // the last -> next = tail
    }

    size_t size(){
        return this->length;
    }

    void addNode(Node * node){
        node -> pre = tail -> pre;
        node -> next = tail;

        tail->pre -> next = node;
        tail -> pre = node;
        this -> length ++;
    }

    void removeNode(Node * node){
        node ->pre -> next = node -> next;
        node -> next -> pre = node -> pre;
        delete node;
        this -> length --;      
    }

    Node * removeFirst(){

        // O(1)
        if (this->head -> next == tail){
            return nullptr;
        }
        Node * first = head ->next;
        removeNode(first);
        return first;
    }
};

class LRU
{
private:
// key -> Node(key, val)
// Node(k1, v1) <-> Node(k2, v2)...
    unordered_map<int, Node *> map;
    DoubleList cache;
    size_t cap;
public:
    void makeRecently(int key){
        Node * node = map[key];
        cache.removeNode(node);
        cache.addNode(node);

    }

    void addRecently(int key, int val){
        Node * node = new Node(key, val);
        cache.addNode(node);
        map[key] = node;
    }

    void deleteKey(int key){
        Node * node = map[key];
        cache.removeNode(node);
        map.erase(key);
    }

    void removeLeastRecently(){
        // head is the least recent
        Node * node = cache.removeFirst();
        map.erase(node->key);
    }

    int get(int key){
        if (!map.count(key)){
            return -1;
        }
        makeRecently(key);
        return map[key]->val;
    }

    void put(int key, int val){
        if (map.count(key)){
            makeRecently(key);
            return;
        }
        Node * node = new Node(key, val);
        if (cap == cache.size()){
            removeLeastRecently();
            // remove the head
        }
        addRecently(key, val);
    } 
};
