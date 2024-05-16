#pragma once

#include "GameTask.hpp"

class GTUpdateState : public GameTask 
{
    public:
    GTUpdateState();
    ~GTUpdateState();

    virtual void perform() override;

};