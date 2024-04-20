#include <iostream>
#include <thread>
#include <chrono>

#define MAX 10
#define MIN 0

void Client(int& clients) {
	while (clients < MAX) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		clients++;
		std::cout << "New client added, num of clients: " << clients << std::endl;
	}
	if (clients == MAX) std::cout << "The limit of clients has been reached!" << std::endl;
}

void Operator(int& clients) {
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		if (clients > MIN) {
			clients--;
			std::cout << "Client is served, num of clients: " << clients << std::endl;
		}
		else {
			std::cout << "All clients served. Closing the queue." << std::endl;
			break;
		}
	}
}

int main() {
	int clients = MIN;
	std::thread t1(Client, std::ref(clients));
	std::thread t2(Operator, std::ref(clients));
		
	t1.join();
	t2.join();	

	return 0;
}