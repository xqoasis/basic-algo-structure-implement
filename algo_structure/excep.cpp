#include <iostream>
#include <exception>

class TempException : public std ::exception
{
public:
    const char * itsMyDefine() const throw() // 自定义的exception class中的exception function
    {
        return "self-defined exception";
    }

};
//这是exception public method，which was overloaded by all son. It will return the reason of exception

int main(){
    int a = 0;
    try
    {
        if (a == 0){
            throw TempException();
        }
        std :: cout << "no exception" << std ::endl;
    }
    catch(TempException& e)
    {
        std::cout << "we catch the slf-defiende ex" << '\n';
        std::cout << e.itsMyDefine() << std::endl;
    }
    catch (...)
    {
        std::cout << "other errors" << std::endl;
    }
    
}
