#pragma once
#include <iostream>
#include <mutex>

class Data {
private:
	int				_int = 0;
	double			_double = 0.0;
	bool			_bool = false;
	std::mutex		_mutex;
public:
	Data(int& i, double& d, bool& b) : _int(i), _double(d), _bool(b) {};
	Data(int&& i, double&& d, bool&& b) : _int(i), _double(d), _bool(b) {};
	Data() : _int(0), _double(0), _bool(false) {};

	Data(Data& other) : _int(other._int), _double(other._double), _bool(other._bool) {};
	Data(Data&& other) noexcept : _int(other._int), _double(other._double), _bool(other._bool) {};

	void operator=(Data& other);
	void operator=(Data&& other) noexcept;

	void Print();
	std::mutex& GetMutex();
};

void SwapLock(Data& alfa, Data& betta);
void SwapScopedLock(Data& alfa, Data& betta);
void SwapUniqueLock(Data& alfa, Data& betta);