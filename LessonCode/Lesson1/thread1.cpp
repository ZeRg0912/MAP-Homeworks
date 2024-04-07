#define _USE_MATH_DEFINES
#include<iostream>
#include<thread>
#include <Windows.h>
#include "Timer.h"

using namespace std;

void func1()
{
	cout << this_thread::get_id() << endl;
	for (int i = 0; i < 10; i++)
	{
		this_thread::sleep_for(100ms);
		consol_parameter::SetColor(15, 0);
		cout << i << " ";
	}
	cout << endl;
}

void func2()
{
	cout << this_thread::get_id() << endl;
	for (int i = 0; i < 10; i++)
	{
		this_thread::sleep_for(100ms);
		consol_parameter::SetColor(10, 0);
		cout << i << " ";
	}
	cout << endl;
}

class A
{
public:
	void operator()()
	{
		cout << __FUNCTION__ << endl;
	}
	void funcClassA()
	{
		cout << __FUNCTION__ << endl;
	}
};

int main_t1()
{
	cout << this_thread::get_id() << endl;
	//thread T1(func1);
	//T1.detach();
	//thread T2(func2);
	//T2.join();
	//if (T1.joinable())
	//	T1.join();
	//else
	//	cout << "Not joinable" << endl;
	A obj;

	thread T3(obj);
	T3.join();
	thread T4(&A::funcClassA, &obj);
	T4.join();

	thread T5([]() {cout << "Lambda" << endl; });
	T5.join();

	return 0;
}
