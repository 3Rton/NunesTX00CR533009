#pragma once

class GameTask 
{

    public:
    GameTask() {};
    ~GameTask() {};

    virtual void perform() = 0;

};