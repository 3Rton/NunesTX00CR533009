#pragma once

#include <iostream>
#include <string>
#include <chrono>

class Timer
{
    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;
    
    public:
    Timer();
    ~Timer();

    void StartTimer();
    void StopTimer(std::string CallSignature);

};