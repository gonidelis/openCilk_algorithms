#include <cilk/cilk.h>
#include "opencilk_reducer.hpp"
#include <cilk/reducer_opadd.h>

#include <iostream>
#include <chrono>

#define N 1'000'000

unsigned int compute(unsigned int i)
{
    return i; // return a value computed from i
}

void sequential_sum()
{
    unsigned int n = N;

    auto start = std::chrono::steady_clock::now();

    unsigned int total = 0;
    // Compute the sum of integers 1..n
    for(unsigned int i = 1; i <= n; ++i)
    {
        total += compute(i);
    }

    std::cout << "[Seq] - total: " << total << std::endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "[Seq] elapsed time: " << elapsed_seconds.count() << "s\n";
}


// When n is passed as a RUNTIME parameter Tapir does not parallelize it
// message: "failed to use divide-and-conquer loop spawning"
void cilk_sum()
{
    unsigned int n = N;

    auto start = std::chrono::steady_clock::now();

    cilk::reducer_opadd<unsigned int> total;
    // Compute 1..n
    cilk_for(unsigned int i = 1; i <= n; ++i)
    {
        total += compute(i);
    }

    std::cout << "[Cilk] - total: " << total.get_value() << std::endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "[Cilk] elapsed time: " << elapsed_seconds.count() << "s\n";

}

int  main(int argc, char* argv[])
{

    cilk_sum();
    sequential_sum();

    // unsigned int correct = (N * (N+1)) / 2;
    std::cout << "correct: " << correct << std::endl;
}   



