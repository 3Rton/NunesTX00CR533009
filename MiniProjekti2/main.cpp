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

#define ASYNC 1

int main()
{
    Robject* objdef = new Robject();
    Robject* obj = new Robject("Bob");

    Log_ptr<Robject> ptrDef(objdef);
    Log_ptr<Robject> ptrBob(obj);

    //deleted functions
    //Log_ptr<Robject> ptrCtor(ptrBob);
    //ptrBob = ptrDef;

    std::cout << "But now the fun is over." << std::endl;
}