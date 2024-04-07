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

void print_number1(shared_future<int> val)
{
	shared_future<int> l1 = val;
	cout << "Result1 = " << l1 .get() << endl;
}
void print_number2(shared_future<int> val)
{
	shared_future<int> l2 = val;
	cout << "Result2 = " << l2.get() << endl;
}

int main()
{
	
	promise<int> pr;
	shared_future<int> fut = pr.get_future();
	auto t1 = async(print_number1, fut);
	auto t2 = async(print_number2, fut);
	int v = 1;
	do
	{
		cin >> v;
		if (v == 10)
			pr.set_value(10);
	} while (v != 0);


	return 0;
}