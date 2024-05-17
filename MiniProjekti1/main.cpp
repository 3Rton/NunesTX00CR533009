#include <iostream>

#include <thread>
#include <future>
#include <mutex>

#include <vector>
#include <queue>

#include "GameTask.hpp"
#include "TaskQueue.hpp"

//Estimate available threads
int STHC = std::thread::hardware_concurrency();
int AvailableThreads = (STHC != 0) ? (AvailableThreads = STHC) : (AvailableThreads = 1);
std::atomic<int> TasksDone(0);

#define ASYNC 1

int main()
{
    int nof_tasks = 10000;
    std::vector<GameTask> TaskVector;
    for (int i = 0; i < nof_tasks; i++)
    {
        GameTask NewTask;
        TaskVector.push_back(NewTask);
    }

    std::cout << "Task Queue created" << std::endl;
    TaskQueue Tasks(AvailableThreads);

    std::cout << "Adding " << nof_tasks << " tasks to " << AvailableThreads << " worker threads." << std::endl;
    for (auto& task : TaskVector)
    {
        Tasks.AddJob(task);
    }

    std::cout << "Tasks Done: " << TasksDone.load() << std::endl;

    std::this_thread::sleep_for( std::chrono::seconds(5) );

    std::cout << "Ending app" << std::endl;
}