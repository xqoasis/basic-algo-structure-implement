// First non-repeating character in a string
// Given any string like “aabbcdefabacd”
// Return the first non-repeating character which in this example is ‘e’.
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


int main(){
    string str = "aabbcdefabacd";
    unordered_map<char ,int> m;
    for (auto c:str){
        m[c] ++; //use hashmap to record
    }

    vector<char> ans;

    for (auto c:str){
        if (m[c] == 1){
            cout << c << endl;
            break;
        }
    }


    return 0;
}




