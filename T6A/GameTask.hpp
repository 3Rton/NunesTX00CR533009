#pragma once

#include<mutex>

class GameTask 
{

    public:
    std::mutex mutex;
    GameTask() {};
    ~GameTask() {};

    virtual void perform() = 0;

};