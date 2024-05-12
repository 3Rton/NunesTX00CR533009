
#include <iostream>

#include "GTUpdateState.hpp"

GTUpdateState::GTUpdateState()
{
}

GTUpdateState::~GTUpdateState()
{
}

void GTUpdateState::perform()
{
    Timer* tt = new Timer();
    tt->StartTimer();
    for(int i = 0; i < 5000000; i++)
    {
        double a = 1000 * 100000;
    }
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "World State Updated" << std::endl;
    tt->StopTimer("GTUpdateState::Perform ");
    
}