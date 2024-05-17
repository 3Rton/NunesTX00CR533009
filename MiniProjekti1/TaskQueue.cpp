#include "TaskQueue.hpp"

TaskQueue::TaskQueue()
{
    CanEnqueue.store(true);

}

TaskQueue::TaskQueue(int nof_threads)
{
    CanEnqueue.store(true);

    if ( nof_threads > 0)
    {
        std::lock_guard<std::mutex> LocalLock(Lock);

        for (int i = 0; i < nof_threads; i++)
        {
            DeployWorker();
        }

    } else {std::cout << "nof_threads must be over 0" << std::endl;}

}

TaskQueue::~TaskQueue() 
{
    std::cout << "Synchronizing workers." << std::endl;
    Join();

    std::cout << "Goodbye, Tasks done at the end: " << TasksDone.load() <<
     std::endl << "From TaskQueue.";
}

void TaskQueue::WorkerRunnable(TaskQueue* const Manager)
{
    while (Manager)
	{
		std::unique_lock<std::mutex> EvaluationLock(Manager->Lock);
		if (Manager->IsPendingDestroy(std::this_thread::get_id()))
		{
			break;
		}

		//auto NewTask(std::move(Manager->Dequeue()));
        auto NewTask(Manager->Dequeue());
        
		if (NewTask)
		{
			EvaluationLock.unlock();

			std::invoke(*NewTask);
		}
		else
		{
			WorkerSignal.wait(EvaluationLock);
		}
	}
}

void TaskQueue::DeployWorker()
{
    Workers.push_back({std::thread(std::bind(&TaskQueue::WorkerRunnable, this, this)), false});
}

void TaskQueue::KillWorker()
{
    Workers.back().second = true;
    Workers.back().first.detach();

    Workers.pop_back();
}

bool TaskQueue::IsPendingDestroy(std::thread::id ID)
{
    for(const auto& Worker : Workers)
    {
        if (Worker.first.get_id() == ID)
		{
			return Worker.second;
		}
    }

    return true;
}

void TaskQueue::Join()
{
    std::unique_lock<std::mutex> QueueLock(Lock);

    if (Workers.size() > 0)
    {
        CanEnqueue.store(false);

		while (!Queue.empty())
		{
			DequeueSignal.wait(QueueLock);
		}

		for (auto& Worker : Workers)
		{
			Worker.second = true;
		}
		WorkerSignal.notify_all();

		QueueLock.unlock();

		for (auto& Worker : Workers)
		{
			Worker.first.join();
		}

		QueueLock.lock();

		Workers.clear();

		CanEnqueue.store(true);
        std::cout << "All workers joined." << std::endl;
	}
    
}

void TaskQueue::Stop()
{
    std::lock_guard<std::mutex> LocalLock(Lock);

    Queue.clear();

    for (auto& Worker : Workers)
    {
        Worker.second = true;
        Worker.first.detach();
    }

    Workers.clear();
    WorkerSignal.notify_all();


}

void TaskQueue::AddJob(GameTask Task)
{
	std::lock_guard<std::mutex> LocalLock(Lock);

	++CurrentWorkID;

	Queue.push_back({ CurrentWorkID, Task });

	WorkerSignal.notify_one();
}

std::optional<GameTask> TaskQueue::Dequeue()
{
    if (Queue.size() > 0)
    {
        DequeueSignal.notify_all();

        GameTask NewTask(Queue.front().second);
        Queue.pop_front();

        return NewTask;
    }

    return std::nullopt;
}
