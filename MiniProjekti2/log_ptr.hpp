#pragma once

#include <iostream>
#include <chrono>

template <class T>
class Log_ptr
{
private:
    T* ObjectPtr = nullptr;
    int* RefCount = nullptr;

public:
    Log_ptr();
    Log_ptr(T* InputPtr);
    Log_ptr(const Log_ptr& InputLogPtr);

    T& operator=(const Log_ptr& InputLogPtr);
    T* operator->();
    T& operator*();

    T* GetObjectPtr();

    std::string GetName();

    ~Log_ptr();

private:
    void __CleanUp__();
};

