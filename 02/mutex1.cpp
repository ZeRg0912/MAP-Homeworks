#define _USE_MATH_DEFINES
#include<iostream>
#include<thread>
#include<mutex>
#include "Timer.h"

using namespace std;

mutex m;

void func1()
{
	lock_guard<mutex> grd(m);
	for (int i = 0; i < 10; i++)
	{
		this_thread::sleep_for(100ms);
		consol_color::SetColor(15, 0);
		cout << i << " ";
	}
	cout << endl;
}

void func2()
{
	//m.lock();
	lock_guard<mutex> grd(m);
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

recursive_mutex m11;
void rec_print(int x)
{
	m11.lock();
	cout << x << " ";
	this_thread::sleep_for(100ms);
	if (x == 0)
	{
		cout << endl;
		m11.unlock();
		return;
	}
	rec_print(--x);
	m11.unlock();
}


int main_mt1()
{
	//thread t1(func1);
	//thread t2(func2);
	//t1.join();
	//t2.join();

	thread t3(rec_print, 6);
	thread t4(rec_print, 4);
	t3.join();
	t4.join();

	return 0;
}

