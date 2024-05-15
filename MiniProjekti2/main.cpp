#include <thread>
#include <future>
#include <mutex>
#include <vector>

#include "log_ptr.hpp"
#include "log_ptr.cpp"
#include "robject.hpp"

//Estimate available threads
int STHC = std::thread::hardware_concurrency();
int AvailableThreads = (STHC != 0) ? (AvailableThreads = STHC) : (AvailableThreads = 1);

std::mutex gmutex;
#define ASYNC 1

int main()
{
    Robject* objdef = new Robject();
    Robject* obj = new Robject("Bob");

    Log_ptr<Robject> logptr(obj);
    Log_ptr<Robject> copyptr(logptr);
}