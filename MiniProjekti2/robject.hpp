#pragma once

#include <iostream>
#include <string>

class Robject
{
    public:
    std::string name{"Default name"}; 

    Robject();
    Robject(std::string name);

    ~Robject();

};