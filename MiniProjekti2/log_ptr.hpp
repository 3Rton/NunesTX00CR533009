#pragma once

#include <iostream>
#include <chrono>

template <class T>
class Log_ptr
{
private:
    T* objPtr = nullptr;

public:
    Log_ptr(T* inPtr);
    Log_ptr(const Log_ptr&) = delete;

    void operator=(const Log_ptr& ptr) = delete;
    
    T* operator->();
    T& operator*();

    std::string GetName();

    ~Log_ptr();
};

