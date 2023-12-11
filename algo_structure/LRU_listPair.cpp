#include <unordered_map>
#include <list>
#include <iostream>

using namespace std;

// template<typename T> 和 template<class T> 区别

template<typename T>
class LRUCache
{
private:
    list<pair<T, T>> li;
    unordered_map<T, list<pair<T, T>>::iterator> map;
    int cap;
public:
    LRUCache(int c);
    ~LRUCache();
    void Put(T key, T value);
    T Get(T key);
};

template<typename T>
LRUCache<T>::LRUCache(int c)
{
    cap = c;
}
template<typename T>
LRUCache<T>::~LRUCache()
{
}

template <typename T>
T LRUCache<T>::Get(T key)
{
    if (map.find(key) != map.end()) {
        // exist
        li.erase(map[key]);
        map[key] = li.insert(li.end(), {key, *map[key]})
    }else {
        return NULL;
    }
}

template <typename T>
void LRUCache<T>::Put(T key, T value)
{
    if (map.find(key) != map.end()) {
        // exist
        li.erase(map[key]);
        map[key] = li.insert(li.end(), {key, *map[key]})
        return;
    }
    // push new
    if (li.size() == cap) {
        // pop
        li.pop_front();
    }
    map[key] = li.insert(li.end(), {key, value});
}


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
    LRUCache<int> lru = LRUCache<int>(3);
    
    lru.Put(1, 1);
    cout << lru.Get(1);
    // LRUCache<int>* lru = new LRUCache<int>(3);
    
    // lru->Put(1, 1);
    // cout << lru->Get(1);
    return 0;
}