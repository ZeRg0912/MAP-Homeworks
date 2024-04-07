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
double square_root(double x)
{
	if (x < 0)
	{
		throw std::out_of_range("x < 0");
	}
	return sqrt(x);
}

void find_number_ex(int exp, promise<int> pr)
{
	random_device rd;
	mt19937 gen{ rd() };
	uniform_int_distribution<> dis(0, 100);
	int value = dis(gen);
	while (value != exp)
	{
		//cout << value << " ";
		//this_thread::sleep_for(50ms);
		value = dis(gen);
	}
	try
	{
		throw 1;
		pr.set_value(value);
	}
	catch (int)
	{
		//pr.set_exception(current_exception());
		pr.set_exception(make_exception_ptr(logic_error("find_number_error")));
	}
}


int main_as2()
{
	try
	{
		future<double> f = async(square_root, -1);
		double res = f.get();
	}
	catch (logic_error err)
	{
		cerr << err.what() << endl;
	}

	promise<int> f_promise;
	future<int> f_future = f_promise.get_future();
	auto res1 = async(find_number_ex, 50, move(f_promise));
	f_future.wait();
	try
	{
		cout << "res" << f_future.get() << endl;
	}
	catch (logic_error err)
	{
		//cout << "Error - " << err << endl;
		cout << "Error - " << err.what() << endl;
	}
	//cout << "res = " << f_future.get();

	auto s1 = async([]() {
		this_thread::sleep_for(10s);
		cout << "10 sec" << endl;
		});
	auto s2 = async([]() {
		this_thread::sleep_for(5s);
		cout << "5 sec" << endl;
		});
	cout << "0 sec" << endl;
	return 0;
}