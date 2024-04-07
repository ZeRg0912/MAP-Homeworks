#define _USE_MATH_DEFINES
#include<iostream>
#include<thread>
#include<mutex>
#include "Timer.h"

using namespace std;
mutex m;

void func1()
{
	//m.lock();
	lock_guard<mutex> L1(m);
	for (int i = 0; i < 10; i++)
	{
		this_thread::sleep_for(100ms);
		consol_color::SetColor(15, 0);
		cout << i << " ";
	}
	cout << endl;
	//m.unlock();
}

void func2()
{
	//m.lock();
	lock_guard<mutex> L1(m);
	for (int i = 0; i < 10; i++)
	{
		this_thread::sleep_for(100ms);
		consol_color::SetColor(10, 0);
		cout << i << " ";
	}
	cout << endl;
	consol_color::SetColor(15, 0);
	//m.unlock();
}

recursive_mutex m1;
void rec_func(int v)
{
	m1.lock();
	cout << v << " ";
	this_thread::sleep_for(50ms);
	if (v == 0)
	{
		cout << endl;
		m1.unlock();
		return;
	}
	rec_func(--v);
	m1.unlock();
}


int main_m1()
{

	//thread t1(func1);
	//thread t2(func2);
	////thread t3;
	////t3 = move(t1);
	//t1.join();
	//t2.join();
	thread t3(rec_func, 6);
	thread t4(rec_func, 4);
	t3.join();
	t4.join();
	return 0;
}
