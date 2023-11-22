#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

vector<string> splitstr(string str) {
    istringstream iss(str);
    string token;
    vector<string> res;
    while (getline(iss, token, ',')) {
        if (token == "")continue;
        istringstream iss (token);
        while (iss >> token) {
            res.push_back(token);
        }
    }
    return res;
};

int main() {

    string str = "1,2,1,,,,3, 12, 3,,4";
    vector<string> nums = splitstr(str);
    for (auto n: nums){
        cout << n << "!";
    }
    return 0;

}