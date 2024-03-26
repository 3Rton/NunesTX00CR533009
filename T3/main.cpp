#pragma once

#include <thread>
#include <vector>

#include <windows.h>
#include <Sysinfoapi.h>

#include "Timer.hpp"
#include "GameTask.hpp"
#include "GTUpdateState.hpp"
#include "GTAnimate.hpp"
#include "GTRender.hpp"


/*
to truly find out the number of available std::threads we'd have to poll the windows api for available memory, divide that by the smallest thread allocation
and experiment from there somehow to see when error intializing a thread can be captured
*/
void AvailableLProcessors()
{
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    int numCPU = (sysinfo.dwNumberOfProcessors) - 4;
    std::cout << numCPU;
}

int AvailableLProcessorCount()
{
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    int numCPU = (sysinfo.dwNumberOfProcessors) - 4;
    return numCPU;
}

int main()
{
    std::vector<GameTask*> tasks;

    for (int i = 0; i < 100; i++)
    {
        tasks.push_back(new GTUpdateState);
    }
    
    for (int i = 0; i < 100; i++)
    {
        tasks.push_back(new GTAnimate);
    }
    
    for (int i = 0; i < 100; i++)
    {
        tasks.push_back(new GTRender);
    }
    
    int number_of_tasks = tasks.size();
    Timer* TaskPerformTimer = new Timer();
    TaskPerformTimer->StartTimer();
    for (int i = 0; i < number_of_tasks; i++)
    {
        //create threads based on the numCPU, make each thread calculate as many tasks->performs as tasks.size()/numCPU
        tasks[i]->perform();
    }
    TaskPerformTimer->StopTimer("Game loop timer: ");

}