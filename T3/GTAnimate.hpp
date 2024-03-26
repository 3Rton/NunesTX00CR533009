#pragma once

#include "GameTask.hpp"
#include "Timer.hpp"

class GTAnimate : public GameTask
{
    public:
    GTAnimate();
    ~GTAnimate();

    virtual void perform() override;
};