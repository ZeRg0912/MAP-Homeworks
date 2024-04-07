#include <algorithm>
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <random>

using namespace std;

int func7(int k)
{
	this_thread::sleep_for(500ms);
	cout << "k=" << k<< endl;
	return k;
}

void find_number(int exp, promise<int> pr)
{
	random_device rd;
	mt19937 gen{ rd() };
	uniform_int_distribution<> dis(0, 100);
	int value = dis(gen);
	while (value != exp)
	{
		cout << value << " ";
		this_thread::sleep_for(50ms);
		value = dis(gen);
	}
	pr.set_value(value);
}

void print_number(future<int>& val)
{
	cout << "Result = " << val.get() << endl;
}

int main_as1()
{
	//future<int> res = async(func7, 88);
	//future<int> res = async(launch::deferred, func7, 88);
	//for (size_t i = 0; i < 10; i++)
	//{
	//	this_thread::sleep_for(100ms);
	//	cout << i << " ";
	//}
	//cout << res.get() << endl;

	//promise<int> f_promise;
	//future<int> f_future = f_promise.get_future();
	//auto res1 = async(find_number, 50, move(f_promise));
	//f_future.wait();
	//cout << "res = " << f_future.get();

	promise<int> pr;
	future<int> fut = pr.get_future();
	thread t(print_number, ref(fut));
	int v = 1;
	do
	{
		cin >> v;
		if (v == 10)
			pr.set_value(10);
	} while (v != 0);


	t.join();
	return 0;
}