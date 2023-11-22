#include <mutex>
#include <thread>
#include <iostream>

using namespace std;

volatile int var = 10;// 保持变量 var 对内存可见性，防止编译器过度优化
//用它声明的类型变量表示可以被某些编译器未知的因素更改，比如：操作系统、硬件或者其它线程等。遇到这个关键字声明的变量，编译器对访问该变量的代码就不再进行优化，从而可以提供对特殊地址的稳定访问。
// volatile 指出 i 是随时可能发生变化的，每次使用它的时候必须从 i的地址中读取，


class rwlock{
private:
    mutex readmtx;
    mutex writemtx;
    int readCnt;
public:
    rwlock(): readCnt(0){}
    void readLock(){
        // 当读写锁中的读锁被某个线程加上时，先加上读互斥锁，这样保证了其他线程不能再读了；
        // 接着，再加上写互斥锁，同时计数加上 1，这样保证了其他线程不能再写了。接着，把读互斥锁释放掉，因为要允许其他线程也能读这个共享变量。
        // 也就是说，多次读时，只需要加一把写锁，表明其他线程暂时不能执行写操作。
        readmtx.lock();
        if (++readCnt == 1) {
            writemtx.lock();
        }
        readmtx.unlock();
    }
    void readUnLock() {
        readmtx.lock();
        if (--readCnt == 0) {
            writemtx.unlock();
        }
        readmtx.lock();
    }
    void writeLock(){
        writemtx.lock();
    }
    void writeUnLock(){
        writemtx.unlock();
    }


};

void Write(rwlock my_rwlock) {
    my_rwlock.writeLock();
    var += 10;
    std::cout << "write var : " << var << std::endl;
    my_rwlock.writeUnLock();
}

void Read(rwlock my_rwlock){
    my_rwlock.readLock();
    std::cout << "read var : " << var << std::endl;
    my_rwlock.readUnLock();
}

int main() {
    rwlock my_rwlock;
    std::vector<std::thread> writers;
    std::vector<std::thread> readers;
    for (int i = 0; i < 10; i++) {  // 10 个写线程
        writers.push_back(std::thread(Write, my_rwlock));  // std::thread t 的写法报错
    }
    for (int i = 0; i < 100; i++) {   // 100 个读线程
        readers.push_back(std::thread(Read, my_rwlock));
    }
    for (auto& t : writers) {   // 写线程启动
        t.join();
    }
    for (auto& t : readers) {   // 读线程启动
        t.join();
    }
    std::cin.get();


    return 0;

}