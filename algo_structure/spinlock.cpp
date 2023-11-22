#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

class Spinlock {
public:
    Spinlock(): flag(ATOMIC_FLAG_INIT){}

    void lock() {
        while (flag.test_and_set(memory_order_acquire)){//spin while waiting
        // true：如果调用前标志被设置（已经被占用）。
        // false：如果调用前标志未被设置（未被占用）。
        }
        
    }
    void unlock() {
        flag.clear(memory_order_release);
    }
private:
    atomic_flag flag;
};

int main() {
    Spinlock spinlock;
    thread t1(
        [&] {
            spinlock.lock();
            cout<<"Thread 1 lcoked" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            spinlock.unlock();
            cout<<"Thread1 unlocked"<<endl;
        }
    );
    thread t2(
        [&] {
            spinlock.lock();
            cout<<"Thread 2 lcoked" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            spinlock.unlock();
            cout<<"Thread2 unlocked"<<endl;
        }
    );

    t1.join();
    t2.join();

    return 0;
}