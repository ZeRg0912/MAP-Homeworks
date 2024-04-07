#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <queue>
#include <iostream>
using namespace std;

bool flag;
mutex ms;

void wait_flag()
{
    unique_lock<mutex> L(ms);
    while (!flag)
    {
        L.unlock();
        this_thread::sleep_for(100ms);
        L.lock();
        cout << "Flag is not set" << endl;
    }
    cout << "Flag was set" << endl;
}

void set_flag()
{
    this_thread::sleep_for(100ms);
    unique_lock<mutex> L(ms);
    flag = true;
    L.unlock();
}

mutex mut;
queue<int> data_queue;
condition_variable data_cond;

void data_preparation_thread()
{
    int cnt = 0;
    while (cnt < 10)
    {
        int const data = rand() % 100;
        std::lock_guard<std::mutex> lk(mut);
        this_thread::sleep_for(200ms);
        data_queue.push(data);
        cout << "Push " << data << endl;
        data_cond.notify_one();
        if (data == 0)
            break;
    }
}

void data_processing_thread()
{
    while (true)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [] {return !data_queue.empty(); });
        int  data = data_queue.front();
        data_queue.pop();
        lk.unlock();
        cout << "  Pop " << data << endl;
        if (data == 0)
            break;
    }
}



int main_m4()
{
    //thread t1(wait_flag);
    //thread t2(set_flag);
    thread t1(data_preparation_thread);
    thread t2(data_processing_thread);
    t1.join();
    t2.join();

    return 0;
}