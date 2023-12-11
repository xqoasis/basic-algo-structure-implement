template<class T>
class SharedPtr
{
private:
T* _pPtr;
int* _pCount;

void Release(){
    if (--(*_pCount) == 0) {
        delete _pPtr;
        delete _pCount;
    }
}
    
public:
    SharedPtr(T* _pPtr);
    SharedPtr(SharedPtr<T> & sp);
    ~SharedPtr();
    SharedPtr<T>& operator=(const SharedPtr<T>& sp){};
};

// construction
template<class T>
SharedPtr<T>::SharedPtr(T* _pPtr):
    _pPtr(_pPtr),
    _pCount(new int(1))
{}

// copy construction
template<class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>& sp)
{
    _pPtr = sp._pPtr;
    _pCount = sp._pCount;
    ++(*_pCount);
}
// delete
template<class T>
SharedPtr<T>::~SharedPtr()
{
    Release();
}
// operator overlaod
template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& sp) {
    if (sp._pPtr != _pPtr) Release();
    _pPtr = sp._pPtr;
    _pCount = sp._pCount;
    ++(*_pCount);
}
