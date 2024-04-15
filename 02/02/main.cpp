#include <iostream>
#include <limits>
#include <iomanip>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include "../Timer.h"
#include <random>

#ifdef max
#undef max
#endif 

#define MIN 0
#define MAX 5
#define SIZE 3'000'000

std::mutex console_mutex;

void ClearConsole() {
    std::cout << "\x1B[2J\x1B[H";
    system("cls");
}

template<typename T>
T ConsoleInput(std::string name) {
    T parameter;
    while (true) {
        std::cout << "Input number of " << name << ": ";
        std::cin >> parameter;
        if (std::cin.fail()) {
            ClearConsole();
            std::cout << "invalid type of parameter, try again!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            return parameter;
        }
    }
}

void Progress(const int& thread_num, const int& length) {
    auto start = std::chrono::steady_clock::now();
    consol_parameter cursor;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(MIN, MAX);

    {
        std::lock_guard<std::mutex> lock(console_mutex);
        cursor.SetPosition(0, thread_num);
        std::cout
            << thread_num
            << '\t'
            << std::this_thread::get_id()
            << "\t["
            << std::string(length + 1, ' ')
            << "]"
            << std::flush;
    }   

    const int pos(17);
    int shift = 0;

    for (int i = 0; i < length + MAX; i += dis(gen)) {
        if (i > length) i = length;

        const size_t size = SIZE;
        std::vector<int> v1(size), v2(size);
        for (auto& value : v1) {
            value = dis(gen);
        }

        std::vector<int> temp = v1;
        v1 = v2; 
        v2 = temp;

        std::unique_lock<std::mutex> lock(console_mutex);
        try {
            cursor.SetColor(2, 0);
            if (dis(gen) == 3) throw std::exception();
        }
        catch (...) {
            cursor.SetColor(4, 0);
        }


        cursor.SetPosition(pos + shift, thread_num);
        std::cout << std::setfill(char(219));
        std::cout << std::setw(i - shift + 1);
        std::cout
            << char(220)
            << std::flush;
        shift = i;
        lock.unlock();

        if (i == length) {
            {
                std::lock_guard<std::mutex> lock(console_mutex); 
                cursor.SetPosition(pos + shift, thread_num);
                std::cout << char(219) << std::flush;
                cursor.SetColor(7, 0);
            }            
            break;
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed_seconds = static_cast<std::chrono::duration<double>>(end - start);
    std::lock_guard<std::mutex> lock(console_mutex); 
    cursor.SetColor(7, 0);
    cursor.SetPosition(length + 20, thread_num);
    std::cout << std::setprecision(8) << std::fixed << elapsed_seconds.count() << "s" << std::flush;
}

int main() {
    int num_threads = ConsoleInput<int>("threads");
    int length = ConsoleInput<int>("length");
    ClearConsole();
    // Table Header
    std::cout 
        << '#' 
        << "\t id"
        << std::string(length / 2, ' ')
        << "Progress Bar"
        << std::string((length / 2), ' ')
        << "Time" 
        << std::endl;

    std::vector<std::thread> threads;
    for (size_t i = 1; i <= num_threads; i++) {
        threads.push_back(std::thread(Progress, i, length - 1));
    }
    for (auto& thread : threads) {
        thread.join();
    }

    consol_parameter cursor; 
    cursor.SetColor(7, 0);
    cursor.SetPosition(0, num_threads + 1);

    return 0;
}
