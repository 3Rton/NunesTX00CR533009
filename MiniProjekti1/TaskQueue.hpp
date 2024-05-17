#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <optional>

#include <vector>
#include <queue>

#include <functional>
#include <utility>

#include "GameTask.hpp"

extern std::atomic<int> TasksDone;

class TaskQueue
{
    private:
    std::mutex Lock;
    std::condition_variable WorkerSignal;
    std::condition_variable DequeueSignal;

    std::atomic<bool> CanEnqueue;

    std::deque<std::pair<int, GameTask>> Queue;
    int CurrentWorkID;

    std::vector<std::pair<std::thread, bool>> Workers;

    void DeployWorker();
    void KillWorker();

    public:
    TaskQueue();
    TaskQueue(int nof_threads);

    ~TaskQueue();

    void AddJob(GameTask Task);

    void Join();
    void Stop();

    void WorkerRunnable(TaskQueue* const Manager);
    bool IsPendingDestroy(std::thread::id ID);

    std::optional<GameTask> Dequeue();

};