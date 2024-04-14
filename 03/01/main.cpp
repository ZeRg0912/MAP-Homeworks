#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <future>

#include "../Lib.h"

int main() {
	int min = 0;
	int max = 100;

	std::cout << "TEST WITH LIST:\n";
	std::list<int> list;
	size_t list_size = Random(2, 10);
	Fill(list, list_size, min, max);
	std::cout << "Before:\n";
	Print(list);
	std::cout << std::string(20, '=');
	std::cout << "\nAfter:\n";	
	std::list<int> sorted_list = SelectionSort(list);
	Print(sorted_list);

	std::cout << "\n\nTEST WITH VECTOR:\n";
	std::vector<int> vector;
	size_t vec_size = Random(2, 10);
	Fill(vector, vec_size, min, max);
	std::cout << "Before:\n";
	Print(vector);
	std::cout << std::string(20, '=');
	std::cout << "\nAfter:\n";
	std::vector<int> sorted_vec = SelectionSort(vector);
	Print(sorted_vec);

	return 0;
}