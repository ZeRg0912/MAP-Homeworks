#include "Data.h"

std::mutex& Data::GetMutex() {
	return _mutex;
};

void Data::Print() {
	_mutex.lock();

	std::cout
		<< "int: " 
		<< _int << '\n' 
		<< "double: " 
		<< _double << "\n" 
		<< "bool: " 
		<< std::boolalpha
		<< _bool 
		<< '\n'
		<< std::string(20, '=')
		<< std::endl;

	_mutex.unlock();
};

void Data::operator=(Data& other) {
	_int = other._int;
	_double = other._double;
	_bool = other._bool;
};

void Data::operator=(Data&& other) noexcept {
	_int = other._int;
	_double = other._double;
	_bool = other._bool;
};

void SwapLock(Data& left, Data& right) {
	left.GetMutex().lock();
	right.GetMutex().lock();

	Data temp = std::move(right);
	right = left;
	left = temp;

	left.GetMutex().unlock();
	right.GetMutex().unlock();
};

void SwapScopedLock(Data& left, Data& right) {
	std::scoped_lock sl(left.GetMutex(), right.GetMutex());

	Data temp = std::move(right);
	right = left;
	left = temp;
};

void SwapUniqueLock(Data& left, Data& right) {
	std::unique_lock<std::mutex> left_mutex(left.GetMutex(), std::defer_lock);
	std::unique_lock<std::mutex> right_mutex(right.GetMutex(), std::defer_lock);

	Data temp = std::move(right);
	right = left;
	left = temp;

	std::lock(left_mutex, right_mutex);
};