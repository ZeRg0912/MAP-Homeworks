#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <Windows.h>
#include <iomanip>

#pragma execution_character_set( "utf-8" )

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#define MIN_VEC_VALUE 0
#define MAX_VEC_VALUE 10

template<typename T>
T ParallelSumOfVectors(const std::vector<T>& vector1, const std::vector<T>& vector2, const int& threads) {
    std::vector<std::thread> thread_pool(threads);
    std::vector<T> partial_sums(threads, 0);

    size_t total_size = std::max(vector1.size(), vector2.size());

    for (int i = 0; i < threads; i++) {
        size_t start = i * total_size / threads;
        size_t end = (i + 1) * total_size / threads;
        if (i == threads - 1) end = total_size;

        thread_pool[i] = std::thread([=, &vector1, &vector2, &partial_sums]() mutable {
            T local_sum = 0;
            for (size_t j = start; j < end; j++) {
                T val1 = (j < vector1.size()) ? vector1[j] : 0; 
                T val2 = (j < vector2.size()) ? vector2[j] : 0;
                local_sum += val1 + val2;
            }
            partial_sums[i] = local_sum;
            });
    }

    for (auto& thread : thread_pool) {
        thread.join();
    }

    T total_sum = 0;
    for (auto& partial_sum : partial_sums) {
        total_sum += partial_sum;
    }

    return total_sum;
}

template<typename T>
 void FillVectorRand(std::vector<T>& vec) {
     for (int i = 0; i < vec.size(); i++) {
        vec[i] = MIN_VEC_VALUE + rand() % (MAX_VEC_VALUE - MIN_VEC_VALUE);
    }
}

 template<typename T>
 std::vector<T> ResizeVector(std::vector<T>& vec, const int& new_size, bool refill_vec_rand = false) {
     size_t old_size = vec.size();
     vec.resize(new_size, 0);
     if (refill_vec_rand) {
         for (size_t i = 0; i < vec.size(); i++) {
             vec[i] = MIN_VEC_VALUE + rand() % (MAX_VEC_VALUE - MIN_VEC_VALUE);
         }
     }
     else {
         for (size_t i = old_size; i < vec.size(); i++) {
             vec[i] = MIN_VEC_VALUE + rand() % (MAX_VEC_VALUE - MIN_VEC_VALUE);
         }
     }
     return vec;
 }

 template<typename T>
 void PrintVector(const std::vector<T>& vec) {
     for (auto value : vec) {
         std::cout << value << " ";
     }
     std::cout << std::endl;
 }

int main() {
    srand(static_cast<int>(time(0)));
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::vector<int> vec1(5);
    std::vector<int> vec2(2);
    FillVectorRand(vec1);
    FillVectorRand(vec2);
    std::vector<int> threads { 1, 2, 4, 8, 16 };
    std::vector<int> size_of_vec { 1000, 10000, 100000, 1000000 };

    std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << "\n\n";
    std::cout << "\t\t  1000\t\t  10000\t\t  100000\t  1000000\n";
    for (auto& thread : threads) {
        std::cout << thread << " потоков\t";
        for (auto& size : size_of_vec) {
            ResizeVector(vec1, size);
            ResizeVector(vec2, size);
            auto start = std::chrono::steady_clock::now();
            ParallelSumOfVectors(vec1, vec2, thread);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            std::cout << std::setprecision(8) << std::fixed << elapsed_seconds.count() << "s\t";
        }
        std::cout << std::endl;
    }
    
    return 0;
}