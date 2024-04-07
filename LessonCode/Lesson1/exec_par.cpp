#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>
using namespace std;

void Sort(vector<int> v) {
    auto start = chrono::high_resolution_clock::now();
    sort(v.begin(), v.end());
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time = end - start;
    cout << "Sort time - " << time.count() << "ms" << endl;
}

void ParallelSort(vector<int> v) {
    auto start = chrono::high_resolution_clock::now();
    sort(execution::par, v.begin(), v.end());
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time = end - start;
    cout << "Parallel Sort time - " << time.count() << "ms" << endl;
}

int main_exec()
{
    vector<int> d(100'000);
    mt19937 gen;
    uniform_int_distribution<int> dis(0, 100'000);
    auto rand_num([=]() mutable { return dis(gen); });
    generate(execution::par, begin(d), end(d), rand_num);
    Sort(d);
    ParallelSort(d);
    return 0;
}
