#pragma once
// OpenMP header
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <limits>
#include <chrono>

void hello_world() {
    printf("\nStart hello_world()\n");
    const auto processor_count = std::thread::hardware_concurrency();
    omp_set_num_threads(processor_count);
#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Welcome from thread = %d\n", tid);

        if (tid == 0) {
            int nthreads = omp_get_num_threads();
            printf("Number of threads = %d: this message from thread #%d\n", nthreads, tid);
        }
    }
    printf("\nFinish hello_world()\n");
}

void cal_sum() {
    printf("\nStart cal_sum()\n");
    int sum = 0;
    int data_size = 100000000;
    int num_threads = 2;
    int workload = data_size / num_threads;
    int* data = new int[data_size];
    for (int i = 0; i < data_size; ++i) {
        data[i] = 1;
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    omp_set_num_threads(num_threads);
#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int local_sum = 0;
        for (int i = tid * workload; i < (tid + 1) * workload; ++i) {
            local_sum += data[i];
        }
        #pragma omp critical
        sum += local_sum;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
        << "[microseconds]" << std::endl;
    assert(sum == data_size);
    printf("\nFinish cal_sum(): assert pass!\n");
}

void cal_max() {
    printf("\nStart cal_max()\n");
    int max = std::numeric_limits<int>::min();
    int data_size = 100000000;
    int num_threads = 2;
    int workload = data_size / num_threads;
    int* data = new int[data_size];
    for (int i = 0; i < data_size; ++i) {
        data[i] = rand() % data_size;
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    omp_set_num_threads(num_threads);

    // OpenMP implementation: start your code here
#pragma omp parallel
    {
        int local_max = std::numeric_limits<int>::min();
        int tid = omp_get_thread_num();
        for (int i = tid * workload; i < (tid + 1) * workload; ++i) {
            if (data[i] > local_max) {
                local_max = data[i];
            }
        }
#pragma omp critical
        {
            if (local_max > max) {
                max = local_max;
            }
        }
    }
    // OpenMP implementation: stop here
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
        << "[microseconds]" << std::endl;
    std::vector<int> vect(data, data + data_size);
    int max_found_by_stl = *std::max_element(vect.begin(), vect.end());
    std::cout << "max found by stl: " << max_found_by_stl << ", max found by OpenMP " << max << std::endl;
    printf("\nFinish cal_max()\n");
}
