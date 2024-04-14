#pragma once
#include <iostream>
#include <random>
#include <list>
#include <vector>
#include <future>
#include <thread>

template<typename T>
T Random(T min, T max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

template<typename T>
void Fill(T& container, const size_t& size, const int& min, const int& max) {
	for (size_t i = 0; i < size; i++) {
		container.push_back(Random(min, max));
	}
}

template<typename T>
void FillString(T& container, const size_t& size, const bool& is_string) {
	for (size_t i = 0; i < size; i++) {
		std::string random_string;
		size_t length = Random(1, 10);
		for (size_t i = 0; i < length; i++) {
			int random_index = Random(0, 128);
			char random_char = static_cast<char>(random_index);
			random_string += random_char;
		}

		std::list<char> target = { '\r', '\n', '\t', '\v' };
		for (auto& ch : target) {
			random_string.erase(std::find(random_string.begin(), random_string.end(), ch), random_string.end());
		}

		container.push_back(random_string);
	}
}

template<typename T>
void Print(T& container) {
	size_t num = 0;
	std::cout << "Size: " << container.size() << std::endl;
	for (auto& val : container) {
		std::cout << "Val#" << num << ": " << val << std::endl;
		num++;
	}
}

template<typename T>
void FindMin(T& container, std::promise<typename T::iterator>& promise) {
	auto it = std::min_element(container.begin(), container.end());
	promise.set_value(it);
}

template <typename T>
T SelectionSort(T& container) {
	T sorted_container;
	while (!container.empty()) {
		std::promise<typename T::iterator> promise;
		std::future<typename T::iterator> future = promise.get_future();

		std::thread thread(FindMin<T>, std::ref(container), std::ref(promise));
		thread.join();

		auto min = future.get();

		sorted_container.push_back(*min);
		container.erase(min);
	}
	return sorted_container;
}

template<typename Iterator, typename Function>
void ForEachParallel(Iterator begin, Iterator end, Function& func) {
	auto total_size = std::distance(begin, end);
	if (total_size == 0) return;

	if (total_size == 1) std::for_each(begin, end, func);
	else {
		Iterator mid = begin;
		std::advance(mid, total_size / 2);
		std::future<void> fut1 = std::async(std::launch::async, ForEachParallel<Iterator, Function>, begin, mid, std::ref(func));
		std::future<void> fut2 = std::async(std::launch::async, ForEachParallel<Iterator, Function>, mid, end, std::ref(func));
		fut1.get();
		fut2.get();
	}
}