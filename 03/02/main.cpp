#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <future>
#include <chrono>
#include <iomanip>

#include "../Lib.h"

int main() {
	int min = 1;
	int max = 5;
	auto square = [](int& val) { val *= val; };

	//auto start = std::chrono::steady_clock::now();
	std::cout << "TEST WITH LIST:\n";
	std::list<int> list;
	size_t list_size = Random(2, 10);
	Fill(list, list_size, min, max);
	std::cout << "Before:\n";
	Print(list);
	std::cout << "After:\n"; 
	ForEachParallel(list.begin(), list.end(), square, 2);
	Print(list);
	/*auto end = std::chrono::steady_clock::now();
	auto elapsed_seconds = static_cast<std::chrono::duration<double>>(end - start);
	std::cout << std::setprecision(8) << std::fixed << elapsed_seconds.count() << "s" << std::flush;*/


	//start = std::chrono::steady_clock::now();
	std::cout << "\n\nTEST WITH VECTOR:\n";
	std::vector<int> vector;
	size_t vec_size = Random(2, 10);
	Fill(vector, vec_size, min, max);
	std::cout << "Before:\n";
	Print(vector);
	std::cout << "After:\n";
	ForEachParallel(vector.begin(), vector.end(), square, 2);
	Print(vector);
	/*end = std::chrono::steady_clock::now(); 
	elapsed_seconds = static_cast<std::chrono::duration<double>>(end - start);
	std::cout << std::setprecision(8) << std::fixed << elapsed_seconds.count() << "s" << std::flush;*/

	return 0;
}