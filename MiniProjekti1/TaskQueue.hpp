#pragma once

#include <thread>

#include <vector>
#include <queue>

#include "GameTask.hpp"

class TaskQueue
{
    private:
    std::vector<std::thread> ThreadPool;
    std::queue<GameTask> TasksQueue;

    public:
    TaskQueue();
    TaskQueue(int nof_threads);

    ~TaskQueue() {};

    void ShoutInfo() {};

    void AddJob(GameTask* task) {};
    void DoWork() {};

};