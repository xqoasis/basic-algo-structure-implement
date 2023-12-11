#include <unordered_map>
#include <vector>

using namespace std;

template<typename T>
class o1list
{
private:
    vector<T> ve;
    unordered_map<T, int> map; // num, index
    int cap;
public:
    o1list(int c);
    ~o1list();
    T getRandom();
    bool Insert(T num);
    bool Delete(T num);
};
template<typename T>
o1list<T>::o1list(int c)
{
    cap = c;
}
template<typename T>
o1list<T>::~o1list()
{
    delete ve;
    delete map;
}
template<typename T>
T o1list<T>::getRandom() {
    return ve[random()%ve.size()]
}
template<typename T>
bool o1list<T>::Insert(T num) {
    if (ve.size() == cap || map.count(num)) {
        return false;
    }
    // exist
    ve.push_back(num);
    map[num] = ve.size() - 1;
    
    return true;
}
template<typename T>
bool o1list<T>::Delete(T num) {
    if (map.find(num) == map.end()) {
        return false;
    }
    int idx = map[val];
    map[ve.back()] = idx;
    swap(ve[map[num]], ve.back());

    ve.pop_back();
    map.erase(num);
    return true;
}

