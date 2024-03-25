#pragma once

class GameTask 
{

    public:
    GameTask() {};
    ~GameTask() {};

    protected:
    virtual void perform() = 0;

};