#include <thread>
#include <future>
#include <mutex>

#include <vector>
#include <queue>

#include "TaskQueue.hpp"

//Estimate available threads
int STHC = std::thread::hardware_concurrency();
int AvailableThreads = (STHC != 0) ? (AvailableThreads = STHC) : (AvailableThreads = 1);

#define ASYNC 1

int main()
{
    TaskQueue tq(AvailableThreads);
}