#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <vector>
using namespace std;

class System{
private:
    vector<int> base;
    unordered_map<int, int>map;
    int capacity;
    int size = 0;

public:
    System(int cap):capacity(cap){};

    bool insert(int val){
        if (size == capacity){
            return false;
        }
        if (map.count(val)){
            return false;
        }
        // no repeat
        map[val] = size;
        base.push_back(val);
        size++;
    }

    bool remove(int val){
        if (map.find(val) == map.end()){
            return false;
        }
        int index = map[val];
        map[base.back()] = index;
        swap(base.back(), base[index]);

        base.pop_back();
        map.erase(val);
        return true;
    }

    int getRandom(){
        return base[rand()%base.size()];
    }

};

int main(){
  System sys(5);
  sys.insert(2);
  sys.insert(3);
  sys.insert(4);
  sys.remove(4);
  cout << sys.getRandom() << endl;
  return 0;

}

