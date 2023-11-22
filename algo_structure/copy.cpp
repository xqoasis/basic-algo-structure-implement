#include<iostream>
using namespace std;

class Line
{
private:
    int * ptr;
public:
    int getLen();
    Line(int len){ // simple construction
        cout << "use the constructor" << endl;
        ptr = new int;
        *ptr = len;
    }
    Line(const Line & obj){
        cout << "use copy cons" << endl;
        ptr = new int;
        *ptr = *obj.ptr;
    }; // copy 

    ~Line(){
        cout << "release memo" << endl;
        delete ptr;
    }

};

int Line::getLen(void){
    return *ptr;
}

void display(Line obj){
    cout << "daxiao" << obj.getLen()<<endl;
}

int main(){
    Line line(10);
    Line line2 = line;
    display(line);
    display(line2);

    return 0;
}
