#include <iostream>
#include <stdio.h>

//max binary_heap

template<typename T>
class MaxHeap{
private:
    int capacity;
    int size;
    T * heap; // //底层的数组
private:
    void filterUp(int index);//从index所在节点，往根节点调整堆
    void filterDown(int begin, int end);//从index所在节点，往根节点调整堆
public:
    MaxHeap(int cap): capacity(cap){};
    ~MaxHeap();

    bool insert(T val);
    bool remove(T val);
    void print();

    T getTop();
    bool createMaxHeap(T a[], int size);

};

template<typename T>
void MaxHeap<T>::filterUp(int index){
    T value = heap[index];
    while (index > 0){
        int indexParent = (index - 1)/2;
        if (value < heap[indexParent]){
            // satisfy
            break;
        }else{
            heap[index] = heap[indexParent];
            index = indexParent;
        }
    }
    heap[index] = value;
};

template<typename T>
bool MaxHeap<T>::insert(T val){
    if (size == capacity){
        return false;
    }
    heap[size] = val;
    filterUp(size);
    size ++;
    return true;  
};

template<typename T>
void MaxHeap<T>::filterDown(int current, int end){
    int child = current*2 + 1;
    T value = heap[current];
    while (child <= end){
        if (child < end && heap[child] < heap[child + 1]){
            //选出两个孩子中较大的孩子
            child ++;
        }
        if (value > heap[child])break; // dont have to rearrange
        else{
            heap[current] = heap[child];
            current = child;
            child = child * 2 + 1;
            // move the index of value
        }
    }
    heap[current] = value; // 
};

template<typename T>
bool MaxHeap<T>::remove(T val){
    if (size == 0){
        return false;
    }
    int index;
    for (index = 0; index < size; ++index){
        if (heap[index] == val){
            break;
        }
    }

    if (index == size){
        return false;
    }

    heap[index] = heap[size - 1];
    filterDown(index, size-1);

    return true;
}

template<typename T>
void MaxHeap<T>::print(){
    for (int i = 0 ; i < size; ++i){
        cout << heap[i] << " ";
    }
}

template<typename T>
T MaxHeap<T>::getTop(){
    if (size == 0){
        return NULL;
    }
    return heap[0];
}

template<typename T>
bool MaxHeap<T> :: createMaxHeap(T a[], int size){
    if (size > capacity){
        return false;
    }
    for (int i = 0; i < size; ++i){
        insert(a[i]);
    }
    return true;
}

