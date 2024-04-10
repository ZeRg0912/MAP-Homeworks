#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>

#define MAX 3
#define MIN 0

void Client(std::atomic<int>& clients, const std::memory_order& flag) {
	while (clients.load(flag) < MAX) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		clients.fetch_add(1, flag);
		std::cout << "New client added, num of clients: " << clients << std::endl;
	}
	if (clients.load(flag) == MAX) std::cout << "The limit of clients has been reached!" << std::endl;
}

void Operator(std::atomic<int>& clients, const std::memory_order& flag) {
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		if (clients.load(flag) > MIN) {
			clients.fetch_sub(1, flag);
			std::cout << "Client is served, num of clients: " << clients << std::endl;
		}
		else {
			std::cout << "All clients served. Closing the queue." << std::endl;
			break;
		}
	}
}

std::string GetFlagName(const enum std::memory_order& flag) {
	switch (flag) {
		case std::memory_order_seq_cst: return "memory_order_seq_cst";
		case std::memory_order_acq_rel: return "memory_order_acq_rel";
		case std::memory_order_release: return "memory_order_release";
		case std::memory_order_acquire: return "memory_order_acquire";
		case std::memory_order_consume: return "memory_order_consume";
		case std::memory_order_relaxed: return "memory_order_relaxed";
		default: return "not finded!";
	}
}

int main() {
	std::atomic<int> clients(MIN);
	std::vector<std::memory_order> flags = {
		std::memory_order_relaxed, // - �� ����������� ��������� � ������� ����������, ��� ����� �������� � ��������������� ������
		std::memory_order_acquire, // - ���� ������� �����������, ��� ����������� �������� �������� ������, ������� ��������� ����� ����������� load
		std::memory_order_consume, // - �� ����������� ��������� �������, ��������� ������� �������� �� load
		std::memory_order_seq_cst, // - ���� ������� ������������ ����� ������� ������� ������, ���������� ��������� � ������� ���������� � ������������ � ������� ���������
		//std::memory_order_acq_rel, - ���� ������� �������� ��������� acquire � release, �� �� �� �������� ��� load
		//std::memory_order_release  - ���� ������� �����������, ��� ������ ���������� �������� ������ �������, �� �� �� �������� ��� load
	};

	for (auto flag : flags) {
		try {
			std::cout << std::string(40, '=') << std::endl;
			std::cout << "new flag selected - " << GetFlagName(flag) << "\n";
			std::thread t1(Client, std::ref(clients), flag);
			std::thread t2(Operator, std::ref(clients), flag);
			std::cout << std::string(40, '=') << std::endl;
			t1.join();
			t2.join();
		}
		catch (const std::exception& e) {
			std::cerr << "Exception error: " << e.what() << std::endl;
		}
	}

	return 0;
}