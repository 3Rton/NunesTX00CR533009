#pragma once

#include "GameTask.hpp"
#include "Timer.hpp"

class GTRender : public GameTask
{
    public:
    GTRender();
    ~GTRender();

    virtual void perform() override;
};