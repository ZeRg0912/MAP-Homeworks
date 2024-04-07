#define _USE_MATH_DEFINES
#include<iostream>
#include<thread>
#include<string>
#include<vector>
#include<mutex>

using namespace std;

thread_local int var = 1;
void F3()
{
	for (size_t i = 0; i < 10; i++)
	{
		this_thread::sleep_for(100ms);
		cout << var++ <<endl;
	}
}
void F4()
{
	for (size_t i = 0; i < 10; i++)
	{
		this_thread::sleep_for(50ms);
		var *= 2;
		cout << var << endl;
	}
}

void add_str(int x, string& s)
{
	s += "def";
	cout << x << " " << s << endl;
}

int func3(int k)
{
	return k * 2;
}
once_flag flag;
void print_n()
{
	cout << "Numbers" << endl;
}

void print(int k)
{
	call_once(flag, print_n);
	cout << k << " ";
}

int main()
{
	cout << thread::hardware_concurrency() << endl;
	//thread T1(F3);
	//thread T2(F4);
	//T1.join();
	//T2.join();
	int a = 10; string s = "abc";
	thread T3(add_str, a, ref(s));
	T3.join();
	cout << s << endl;

	int res;
	thread T4([&]() {res = func3(10); });
	T4.join();
	cout << res << endl;

	vector<thread> T;
	for (size_t i = 0; i < 10; i++)
	{
		T.push_back(thread(print, i));
	}
	for (auto& thr : T)
	{
		thr.join();
	}

	return 0;
}
