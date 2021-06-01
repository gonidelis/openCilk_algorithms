#include <cilk/cilk.h>
#include "opencilk_reducer.hpp"
#include <cilk/reducer_opadd.h>

#include <iostream>
#include <chrono>
#include <fstream>

#define N 1'000'000
int test_count = 100;

unsigned int compute(unsigned int i)
{
    return i^2 + 10 * i + 1024; // return a value computed from i
}

int measure_seq_sum(uint16_t n)
{
    // unsigned int n = N;

    // auto start = std::chrono::steady_clock::now();

    unsigned int total = 0;
    // Compute the sum of integers 1..n
    for(unsigned int i = 1; i <= n; ++i)
    {
        total += compute(i);
    }

    return total;

    // std::cout << "[Seq] - total: " << total << std::endl;

    // auto end = std::chrono::steady_clock::now();
    // std::chrono::duration<double> elapsed_seconds = end-start;
    // std::cout << "[Seq] elapsed time: " << elapsed_seconds.count() << "s\n";
}


// When n is passed as a RUNTIME parameter Tapir does not parallelize it
// message: "failed to use divide-and-conquer loop spawning"
void measure_cilk_sum(uint16_t n)
{
    // unsigned int n = N;

    // cilk_for(unsigned int i = 1; i <= 2; ++i)
    // {}

    // for(unsigned int n = 1'000 ; n < 10'000'000 ; n += 10000 )
    // {

    // int n = 100'000'000'000;

    // auto start = std::chrono::high_resolution_clock::now();

    cilk::reducer_opadd<int> sum;

    //defining the sum as a reducer with an int value
    cilk_for (int i = 1; i <= n; ++i)
    {
        sum += compute(i);
    }

    if(sum.get_value() != measure_seq_sum(n))
    {
        std::cout << "Error!" << std::endl;
    }

    // auto end = std::chrono::high_resolution_clock::now();
    // cilk_sync;
    // std::chrono::duration<double, std::milli> elapsed_seconds = end-start;
    // if (n != 1000)
    //     std::cout << /*"[Cilk] elapsed time: " */ n << "," << elapsed_seconds.count() << "\n";
    // // }
    

}

double averageout_cilk_sum(uint16_t n)
{
    auto start = std::chrono::high_resolution_clock::now();

    // average out 100 executions to avoid varying results
    for (auto i = 0; i < test_count; i++)
    {
        measure_cilk_sum(n);
    }

    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> elapsed_seconds = end-start;
    return elapsed_seconds.count() / test_count;
}

double averageout_seq_sum(uint16_t n)
{
    auto start = std::chrono::high_resolution_clock::now();

    // average out 100 executions to avoid varying results
    for (auto i = 0; i < test_count; i++)
    {
        measure_seq_sum(n);
    }

    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> elapsed_seconds = end-start;
    return elapsed_seconds.count() / test_count;
}

int  main(int argc, char* argv[])
{

    std::ofstream f;
    f.open ("./times.csv");
    f << "n,par,seq" << std::endl;

    for(unsigned int n = 1 ; n < 100 ; n += 1 )
    {

        auto time = averageout_cilk_sum(n);
        f << n << "," << time << ',';
        time = averageout_seq_sum(n);
        f << time << std::endl;
        
        // f << std::endl;
        // unsigned int correct = (N * (N+1)) / 2;
    }

    f.close();

    return 0;

}   



