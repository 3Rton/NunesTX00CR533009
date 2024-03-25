#pragma once

#include "GameTask.h"

class GTUpdateState : public GameTask 
{
    public:
    GTUpdateState();
    ~GTUpdateState();

    virtual void perform() override;

};