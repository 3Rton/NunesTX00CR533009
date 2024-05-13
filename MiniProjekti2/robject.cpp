#include "robject.hpp"

Robject::Robject() {}

Robject::Robject(std::string inputname) 
{
    name = inputname;
}

Robject::~Robject() 
{
    std::cout << "No one saved " << name << std::endl;
}