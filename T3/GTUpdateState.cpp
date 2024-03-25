#pragma once

#include <iostream>

#include "GTUpdateState.h"

GTUpdateState::GTUpdateState()
{
    std::cout << "made it to constructor" ;
}

GTUpdateState::~GTUpdateState()
{

}

void GTUpdateState::perform()
{
    for(int i = 0; i < 5000000; i++)
    {
        double a = 1000 * 100000;
    }

    std::cout << "World State Updated" << std::endl;
}