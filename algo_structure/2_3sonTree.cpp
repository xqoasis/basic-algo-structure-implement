#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int judgelevel(int level){
    if (level %2 != 0){
        return 2;
    }
    return 3;
}

vector<int> getPath(int n){
    int level = 1;
    int low = 1, high = 1;

    while (high < n){
      int tl = high + 1;
      high += (high - low + 1) * judgelevel(level);
      low = tl;
      level ++; 
    }

    int size = high - low + 1;
    //cout << "size" << size << endl;

    int index = n - low;
    //cout << "index" << index << endl;

    // get the path

    level = 1;
    int cnt = 1;
    high = low = 1;

    vector<int> res;

    while (cnt < n){
        res.push_back(cnt);

        int childnum = judgelevel(level);
        int leftchild = high + (cnt - low)*childnum + 1;

        int div = size / childnum;  // size is future size, seperate in current children group(3 / 2)
        // div 是每一个group的数量
        // index / div 决定在哪一个group （which son）


        cnt = leftchild + (index/div);

        // final level decrease
        size /= childnum;
        index %= size; // 这个group内，从low 到high
        level ++;

        //update low and high
        int temp = high + 1;
        high += (high - low + 1) * childnum;
        low = temp;


    }

    res.push_back(cnt);
    return res;

}

int main(){
    vector<int> res = getPath(17);

    cout << "the ans is "<< endl;

    for (auto i : res){
        cout << i<< endl;
    }

    return 0;
}