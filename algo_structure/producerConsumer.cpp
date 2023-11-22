#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <chrono>
#include <vector>



using namespace std;

mutex mtx;
condition_variable cv; //wait时释放mutex锁，等待唤醒
queue<int> bufferQueue;
#define PRODUCER_BUFFER_NUM 10
int dataValue = 0;

void Producer() {
    while (1) {
        this_thread::sleep_for(chrono::milliseconds(100));
        unique_lock<mutex> lk(mtx); /*这个互斥量是用于互斥bufferQueue的push pop的*/

        // producer keep blocked waiting for notice
        // avoid fake notice, once was notified, we should check bufferQueue is available or not, otherwise keep waiting
        // if we can produce (notify + checked) -> operation -> notify consumer
        while (bufferQueue.size() >= PRODUCER_BUFFER_NUM) {
            cv.wait(lk);
        }
        // checked
        cout << "Producer data" << dataValue << "buffer size" << bufferQueue.size() << endl;
        bufferQueue.push(dataValue ++);

        //notify consumer
        cv.notify_all();
    }
}

void Consumer() {
    // Consumer keep consuming
    while (1) {
        this_thread::sleep_for(chrono::milliseconds(100));
        unique_lock<mutex> lk(mtx);

        // wait until notified (means that there is data in buffer), check
        // checked -> consume
        while (bufferQueue.empty()) {
            cv.wait(lk);
        }
        cout << "Consumer data" << bufferQueue.front() << "buffer size" << bufferQueue.size() << endl; 
        bufferQueue.pop();

        cv.notify_all();

    }
}

int main() {

    vector<std::thread> threads;
    threads.push_back(std::thread(&Producer));
    threads.push_back(std::thread(&Producer));
    threads.push_back(std::thread(&Producer));
    threads.push_back(std::thread(&Consumer));
    
    for(auto &t:threads){
        t.join();
    }
}

