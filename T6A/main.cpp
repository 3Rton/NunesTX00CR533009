#include <thread>
#include <future>
#include <mutex>
#include <vector>

#include "Timer.hpp"
#include "GameTask.hpp"
#include "GTUpdateState.hpp"
#include "GTAnimate.hpp"
#include "GTRender.hpp"

//Estimate available threads
int STHC = std::thread::hardware_concurrency();
int AvailableThreads = (STHC != 0) ? (AvailableThreads = STHC) : (AvailableThreads = 1);

#define ASYNC 1

int main()
{
    std::vector<GameTask*> tasks;
    std::vector<std::future<void>> taskhandles;

    for (int i = 0; i < 1000; i++)
    {
        tasks.push_back(new GTUpdateState);
    }
    for (int i = 0; i < 1000; i++)
    {
        tasks.push_back(new GTAnimate);
    }
    for (int i = 0; i < 1000; i++)
    {
        tasks.push_back(new GTRender);
    }
    
    int number_of_tasks = tasks.size();
    Timer* TaskPerformTimer = new Timer();
    TaskPerformTimer->StartTimer();

    #if ASYNC == 0
    for(auto& element : tasks)
    {
        element->perform();
    }

    #elif ASYNC == 1
    for(auto& element : tasks)
    {
        taskhandles.push_back(std::async(std::launch::async, &GameTask::perform, element));
    }

    for(auto& element : taskhandles)
    {
        element.get();
    }
    #endif

    TaskPerformTimer->StopTimer("Game loop timer: ");

}