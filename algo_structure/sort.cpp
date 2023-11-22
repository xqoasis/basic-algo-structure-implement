#include <iostream>
#include <algorithm>
class Students
{
private:
public:
    std::string name;
    int score;
    void show(){
        std::cout<<"name is " << name << std ::endl;
    }

};
bool cmp(Students a, Students b){
    return a.score>b.score?1:0;
}
int main(){
    std::cout << "stu num is:"<< std::endl;
    int stu_num;
    while (std::cin>> stu_num){
        std::cout << "please input name and score" << std::endl;
        Students stu[stu_num];
        for (int i = 0; i < stu_num; ++i){
            std::cin>> stu[i].name >> stu[i].score;
        }
        std ::sort(stu, stu+stu_num, cmp);
        for (auto s:stu){
            std::cout<<s.name<<" ";
        }
    }

    

    return 0;
}