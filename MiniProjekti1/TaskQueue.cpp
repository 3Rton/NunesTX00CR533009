#include "TaskQueue.hpp"

TaskQueue::TaskQueue()
{

}

TaskQueue::TaskQueue(int nof_threads)
{
    for (int i = 0; i < nof_threads; i++) 
    {
        //std::thread t(&TaskQueue::DoWork);
        //ThreadPool.push_back(t);
    };
  
}

