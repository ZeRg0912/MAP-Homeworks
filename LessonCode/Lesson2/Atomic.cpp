#define _USE_MATH_DEFINES
#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include "Timer.h"

using namespace std;

class Mytex
{
	atomic_flag flag = ATOMIC_FLAG_INIT;
public:
	Mytex() = default;
	void lock()
	{
		while (flag.test_and_set(memory_order_acquire));
	}
	void unlock()
	{
		flag.clear(memory_order_release);
	}


} sm1;


void func10()
{
	sm1.lock();
	for (int i = 0; i < 10; i++)
	{
		consol_color::SetColor(15, 0);
		cout << i << " ";
	}
	cout << endl;
	sm1.unlock();
}

void func20()
{
	sm1.lock();
	for (int i = 0; i < 10; i++)
	{
		consol_color::SetColor(10, 0);
		cout << i << " ";
	}
	cout << endl;
	consol_color::SetColor(15, 0);
	sm1.unlock();
}

int main()
{
	//thread t1(func10);
	//thread t2(func20);
	//t1.join();
	//t2.join();
	 
	atomic<bool> F(true);
	F = false;
	F.store(false);
	F.exchange(true, memory_order_acquire);
	cout << boolalpha << F.load() << endl;

	atomic<int> V;
	V = 10;
	int K = 100000;
	cout << V.compare_exchange_weak(K, 100) << endl;
	cout << V << endl;
	cout << K << endl;
	cout << V.compare_exchange_weak(K, 100) << endl;
	cout << V << endl;

	return 0;
}
