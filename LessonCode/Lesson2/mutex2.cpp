#define _USE_MATH_DEFINES
#include<iostream>
#include<thread>
#include<mutex>
#include "Timer.h"

using namespace std;

class some_data
{
	int a = 10;
	std::string b = "abc";
public:
	void change_data() 
	{
		a += 15;
		b += "dec";
	};
	void print()
	{
		cout << a << " " << b << endl;
	}
};
class data_wrapper
{
private:
	some_data data;
	std::mutex m;
public:
	template<typename Function>
	void process_data(Function func)
	{
		std::lock_guard<std::mutex> l(m);
		func(data);
	}
};

some_data* unprotected;
void malicious_function(some_data& protected_data)
{
	unprotected = &protected_data;
}


int main_m2()
{
	data_wrapper x;
	x.process_data(malicious_function);
	unprotected->change_data();
	unprotected->print();

	return 0;
}
