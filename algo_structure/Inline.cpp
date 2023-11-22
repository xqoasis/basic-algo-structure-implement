#include <iostream>

using namespace std;

inline void useMost(){
    cout << "neilian" << endl;
}

int main(){
    for (int temp = 0; temp < 10; temp ++){
        useMost();
    }

    return 0;
} 