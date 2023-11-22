#include <iostream>
#include <vector>
#include <algorithm>  
using namespace std;

int main(){
    string ans = "";
    string encodeString = "101411797877682311117";
    reverse(encodeString.begin(), encodeString.end());
    int i = 0;
    while (i < encodeString.length()) {
        if (encodeString[i] == '1'){
            int temp = atoi(encodeString.substr(i, 3).c_str());
            char c = temp;
            ans += c;  
            i+= 3;

        }else{
            int temp = atoi(encodeString.substr(i, 2).c_str());
            char c = temp;
            ans += c;  
            i+=2;
        }
            
    }
    cout << ans << endl;




    return 0;
}