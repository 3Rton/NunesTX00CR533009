#pragma once

#include <iostream>

#include <windows.h>
#include <Sysinfoapi.h>

namespace GameplayStatics 
{

    SYSTEM_INFO sysinfo;

    void AvailableLProcessors()
    {
        GetSystemInfo(&sysinfo);
        int numCPU = (sysinfo.dwNumberOfProcessors) - 4;
        std::cout << numCPU;
    }

    //to truly find out the number of available std::threads we'd have to poll the windows api for available memory, divide that by the smallest thread allocation
    //and experiment from there somehow to see when error intializing a thread can be captured

}