#pragma once

#include <mutex>
#include <atomic>

extern std::atomic<int> TasksDone;

class GameTask 
{
    private:
    std::mutex io_mutex;

    public:
    GameTask() {};
    GameTask(const GameTask &InputTask) 
    {};
    ~GameTask() {};

    void operator()()
    {
        perform();
    };

    void perform()
    {
        for (int i = 0; i < 5000000; i++)
        {
            double a = 1000 * 100000;
        }

        TasksDone++;
    };
};