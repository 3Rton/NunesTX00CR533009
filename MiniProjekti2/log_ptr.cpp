#include "log_ptr.hpp"

template <class T>
Log_ptr<T>::Log_ptr( T* inPtr ) : objPtr(inPtr) 
{
    std::cout << "At " << std::chrono::system_clock::now() << ", " << GetName() << " has been abducted at " << objPtr << std::endl;
}

template <class T>
T* Log_ptr<T>::operator->()
{
    std::cout << "At " << std::chrono::system_clock::now() << ", " << GetName() << " -> " << objPtr << std::endl;
    return objPtr;
}

template <class T>
T& Log_ptr<T>::operator*()
{
    std::cout << "At " << std::chrono::system_clock::now() << ", " << GetName() << " * " << objPtr << std::endl;
    return *objPtr;
}

template <class T>
std::string Log_ptr<T>::GetName()
{
    return objPtr->name;
}

template <class T>
Log_ptr<T>::~Log_ptr() 
{
    std::cout << "At " << std::chrono::system_clock::now() << ", " << GetName() << " has been murdered at " << objPtr << std::endl;
    objPtr->~Robject();
}