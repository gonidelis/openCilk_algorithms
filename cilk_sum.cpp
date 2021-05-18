#include <cilk/cilk.h>
#include "opencilk_reducer.hpp"
#include <cilk/reducer_opadd.h>

#include <iostream>
#include <chrono>

unsigned int compute(unsigned int i)
{
    return i; // return a value computed from i
}

void sequential_sum(unsigned int n)
{
    auto start = std::chrono::steady_clock::now();

    unsigned int total = 0;
    // Compute the sum of integers 1..n
    for(unsigned int i = 1; i <= n; ++i)
    {
        total += compute(i);
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "[Seq] elapsed time: " << elapsed_seconds.count() << "s\n";
}

void cilk_sum(unsigned int n)
{
    auto start = std::chrono::steady_clock::now();

    cilk::reducer_opadd<unsigned int> total;
    // Compute 1..n
    cilk_for(unsigned int i = 1; i <= n; ++i)
    {
        total += compute(i);
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "[Cilk] elapsed time: " << elapsed_seconds.count() << "s\n";

}

int  main(int argc, char* argv[])
{
    unsigned int n = 1000000;

    if(argc == 2 )
    {
        n = std::atoi(argv[1]);
    }

    cilk_sum(n);

    sequential_sum(n);

    // unsigned int correct = (n * (n+1)) / 2;
}   