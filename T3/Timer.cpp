#include "Timer.hpp"


Timer::Timer()
{

}

Timer::~Timer()
{

}

void Timer::StartTimer()
{
    t1 = std::chrono::steady_clock::now();
}

void Timer::StopTimer(std::string CallSignature)
{
    t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << CallSignature + " timer returned: " << time_span.count() << " seconds. \n";

    delete this;
}