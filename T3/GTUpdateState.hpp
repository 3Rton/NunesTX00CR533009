#pragma once

#include "GameTask.hpp"
#include "GTRender.hpp"
#include "Timer.hpp"

class GTUpdateState : public GameTask 
{
    public:
    GTUpdateState();
    ~GTUpdateState();

    virtual void perform() override;

};