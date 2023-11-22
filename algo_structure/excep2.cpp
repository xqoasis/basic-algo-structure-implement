#include <iostream>

double division(int a, int b){
    if (b == 0){
        throw "000"; // we throw a const char* type exception
    }
    return (a/b);
}

int main(){
    int a= 1, b = 0;
    double z = 0;
    try
    {
        z = division(a,b);
        std ::cout << z << std ::endl;
    }
    catch(const char* tempo) // when catch, we must use const char* type
    {
        std ::cerr << tempo << std ::endl;
        // tempo is a name of what we throww
    }

    return 0;
    
}