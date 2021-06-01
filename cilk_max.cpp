#include <cilk/cilk.h>
#include "opencilk_reducer.hpp"
#include <cilk/reducer_max.h>

#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <random>
#include <exception>

#define N 1'000'000

int test_count = 100;

unsigned int seed = std::random_device{}();
std::mt19937 gen(seed);


int measure_seq_max(std::vector<int> const& vec)
{


    int max = vec[0];
    // Compute the max of integers 1..n
    for(unsigned int i = 1; i <= vec.size(); ++i)
    {
        if(vec[i] > max)
        {
            max = vec[i];
        }
    }

    return max;
}


void measure_cilk_max(std::vector<int> const& vec)
{

    cilk::reducer<cilk::op_max<int> > rm;
    cilk_for (int i = 0; i < vec.size(); ++i)
    {
        rm->calc_max(vec[i]);    // *rm = cilk::max_of(*max, vec[i])
    }
    

    // // TESTING. DON'T ENABLE IF BENCHMARKING RUNTIME
    // if(measure_seq_max(vec) !=  rm.get_value())
    // {
    //     std::cout << "Error!" << rm.get_value() << "!=" << measure_seq_max(vec) << std::endl;
    //     throw std::exception();
    // }
    
    // std::cout << "maximum value is " << rm.get_value() << std::endl;


}

double averageout_cilk_max(std::vector<int> const& vec)
{
    


    auto start = std::chrono::high_resolution_clock::now();

    // average out 100 executions to avoid varying results
    for (auto i = 0; i < test_count; i++)
    {
        measure_cilk_max(vec);
    }

    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> elapsed_seconds = end-start;
    return elapsed_seconds.count() / test_count;
}

double averageout_seq_max(std::vector<int> const& vec)
{
    auto start = std::chrono::high_resolution_clock::now();

    // average out 100 executions to avoid varying results
    for (auto i = 0; i < test_count; i++)
    {
        measure_seq_max(vec);
    }

    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> elapsed_seconds = end-start;
    return elapsed_seconds.count() / test_count;
}

int  main(int argc, char* argv[])
{

    std::ofstream f;
    f.open ("max_times.csv");
    f << "n,par,seq" << std::endl;

    for(int n = 10 ; n < 1000000 ; n += 100 )
    {
        std::vector<int> vec(n);
        std::iota(
            std::begin(vec), std::end(vec), gen() % 1000);

        auto time = averageout_cilk_max(vec);
        f << n << "," << time << ',';
        // time = averageout_seq_max(vec);
        // f << time << std::endl;
        
        f << std::endl;
        // unsigned int correct = (N * (N+1)) / 2;
    }

    f.close();

    return 0;

}   



