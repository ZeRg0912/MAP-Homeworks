#define _USE_MATH_DEFINES
#include<iostream>
#include<thread>
#include<mutex>
#include<vector>

using namespace std;
mutex m1;
mutex m2;

void deadlock_func_1()
{
    cout << "Старт функции deadlock_func_1..." << endl;
    scoped_lock L{ m1,m2 };
    //lock_guard<mutex> L1{ m1, adopt_lock}; 
    //unique_lock<mutex> L1{ m1, defer_lock};
    this_thread::sleep_for(100ms);
    cout << "Захват мьютекса m1..." << endl;
    //unique_lock<mutex> L2{ m2, defer_lock };
    //lock(L1, L2);
    cout << "Never print A" << endl;
}

void deadlock_func_2()
{
    //lock(m1, m2);
    scoped_lock L{ m1,m2 };
    cout << "Старт функции deadlock_func_2..." << endl;
    //lock_guard<mutex> L2{ m2, adopt_lock };
    //unique_lock<mutex> L2{ m2, defer_lock };
    this_thread::sleep_for(200ms);
    cout << "Захват мьютекса m2..." << endl;
    //lock_guard<mutex> L1{ m1, adopt_lock };
    //unique_lock<mutex> L1{ m1, defer_lock };
    //lock(L1, L2);
    cout << "Never print B" << endl;
}

int main_m3()
{
	setlocale(LC_ALL, "Russian");
	thread t1(deadlock_func_1);
	thread t2(deadlock_func_2);
	t1.join();
	t2.join();


	system("Pause");
	return 0;
}
