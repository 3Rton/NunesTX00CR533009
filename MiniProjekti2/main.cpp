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

    std::cout << "Test arrow operator for getting name " << ptrBob->name << std::endl;
    std::cout << "Test dereference operator for creating Robject " << std::endl;
    Robject* newRobject = &(*ptrBob);
    std::cout << newRobject;
}