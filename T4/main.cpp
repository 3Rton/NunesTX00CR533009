#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include <chrono>
#include <thread>
#include <future>

//Estimate available threads
int STHC = std::thread::hardware_concurrency();
int AvailableThreads = (STHC != 0) ? (AvailableThreads = STHC) : (AvailableThreads = 1);

//Init sizes
int DataVectorSize = 30000000;
int RandomNumberRange = 1000;

//fill vector with random stuff
void PopulateVector(std::vector<int> &input)
{
    std::mt19937 rng;
    std::uniform_int_distribution<> dist(0, RandomNumberRange);

    for(int& element : input)
    {
        element = dist(rng);
    }
}

std::vector< std::pair<std::vector<int>::iterator, std::vector<int>::iterator> > GetChunkRanges(std::vector<int>& input)
{
    std::vector< std::pair<std::vector<int>::iterator, std::vector<int>::iterator> > ListOfIterators;
    int Length = input.size() / AvailableThreads;

    std::vector<int>::iterator a = input.begin();
    std::vector<int>::iterator b = ( input.begin() + Length);

    for(int i = 0; i < AvailableThreads; i++)
    {
        auto pair = std::make_pair(a, b);
        ListOfIterators.push_back( pair );

        std::advance(a, Length);
        std::advance(b, Length);

    }

    if (ListOfIterators.back().second != input.end() )
    {
        ListOfIterators.back().second = input.end();
    }

    return ListOfIterators;
}

int ParallelSum(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::vector<int>& data)
{
    
    int sum = std::accumulate(begin, end, 0);
    return sum;
}

int ParallelAccumulate(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    return std::accumulate(begin, end, 0);
}

std::vector<std::future<int>> CollectFutures (std::vector<int>& input, std::vector< std::pair<std::vector<int>::iterator, std::vector<int>::iterator> > ranges)
{
    std::vector<std::future<int>> futures;

    for (auto element : ranges)
    {
        //futures.push_back(std::async(std::launch::async, ParallelSum, element.first, element.second, std::ref(input) ) );
        futures.push_back(std::async(std::launch::async, ParallelAccumulate, element.first, element.second) );
    }
    
    return futures;
}


int main()
{
    std::vector<int> DataVector(DataVectorSize);
    PopulateVector(DataVector);

    //Timing Linear Concurrent Sum
    auto b1Start = std::chrono::high_resolution_clock::now();
    int ConcurrentSum = std::accumulate(DataVector.begin(), DataVector.end(), 0);
    auto b1End = std::chrono::high_resolution_clock::now();

    //Timing Parrallel Async Sum
    auto b2Start = std::chrono::high_resolution_clock::now();
    std::vector< std::pair<std::vector<int>::iterator, std::vector<int>::iterator> > RangesVector = GetChunkRanges(DataVector);
    std::vector<std::future<int>> FuturesVector = CollectFutures(DataVector, RangesVector);
    int ParallelSumResult = 0;

    for (auto& element : FuturesVector)
    {
        ParallelSumResult += element.get();
    }
    auto b2End = std::chrono::high_resolution_clock::now();

    std::cout << "Concurrent Linear Sum: "<< ConcurrentSum << std::endl << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(b1End - b1Start).count() << "ns" << std::endl
              << "Parallel Sum: "<< ParallelSumResult << std::endl << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(b2End - b2Start).count() << "ns" << std::endl
              << "Parallel was: " << ((std::chrono::duration_cast<std::chrono::nanoseconds>(b1End - b1Start).count()) - (std::chrono::duration_cast<std::chrono::nanoseconds>(b2End - b2Start).count()))/1000000
              << " milliseconds faster." << std::endl;
}