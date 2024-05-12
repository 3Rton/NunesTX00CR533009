#pragma once

#include <iostream>
#include <chrono>
#include <future>
#include <vector>
#include <random>
#include <execution>
#include <algorithm>

int main()
{
    int N = 10000000;

    std::vector<int> ListNums;

    for(int i = 0; i < N; i++)
    {
        ListNums.push_back(i);
    }

    auto s1 = std::chrono::high_resolution_clock::now();
    std::for_each(std::execution::seq, ListNums.begin(), ListNums.end(), [](int &i) {++i;} );
    auto e1 = std::chrono::high_resolution_clock::now();
    auto DurationSeq = std::chrono::duration_cast<std::chrono::nanoseconds>(e1 - s1);

    s1 = std::chrono::high_resolution_clock::now();
    std::for_each(std::execution::par, ListNums.begin(), ListNums.end(), [](int &i) {++i;} );
    e1 = std::chrono::high_resolution_clock::now();
    auto DurationPar = std::chrono::duration_cast<std::chrono::nanoseconds>(e1 - s1);

    s1 = std::chrono::high_resolution_clock::now();
    std::for_each(std::execution::par_unseq, ListNums.begin(), ListNums.end(), [](int &i) {++i;} );
    e1 = std::chrono::high_resolution_clock::now();
    auto DurationParUnseq = std::chrono::duration_cast<std::chrono::nanoseconds>(e1 - s1);

    std::cout << "Seq took " << DurationSeq.count() << " nanoseconds." << std::endl;
    std::cout << "Par took " << DurationPar.count() << " nanoseconds." << std::endl;
    std::cout << "ParUnseq took " << DurationParUnseq.count() << " nanoseconds." << std::endl;

    //seq seems to be >2x slower pretty consistently with ParUnseq being slightly faster than Par
    //sequential is the default step by step execution
    //par is the parallel policy where multiple threads are used
    //parunseq allows using more hardware stuff but might not always give the same result with execution order not being guaranteed


}