#include "log_ptr.hpp"

template <class T>
Log_ptr<T>::Log_ptr() : ObjectPtr(nullptr), RefCount(new int(0))
{}

template <class T>
Log_ptr<T>::Log_ptr( T* InputPtr ) : ObjectPtr(InputPtr), RefCount(new int(1))
{
    std::cout << "At " << std::chrono::system_clock::now() 
    << ", " << GetName() << " has been abducted at " << ObjectPtr 
    << " Reference Count: " << *RefCount << std::endl;
}

template <class T>
Log_ptr<T>::Log_ptr( const Log_ptr& InputLogPtr )
{
    this->ObjectPtr = InputLogPtr.ObjectPtr;
    this->RefCount = InputLogPtr.RefCount;

    if (InputLogPtr.ObjectPtr != nullptr)
    { 
        (*this->RefCount)++;
    }
    
    std::cout << "At " << std::chrono::system_clock::now() 
    << ", new LogPtr was Copyconstructed of, " << GetName() << " at " << ObjectPtr 
    << " Reference Count: " << *RefCount << std::endl;
}

template <class T>
Log_ptr<T>::~Log_ptr() 
{
    std::cout << "At " << std::chrono::system_clock::now() << ", Log Pointer of: " << GetName() << " has been murdered at " << ObjectPtr << std::endl;
    this->__CleanUp__();
}

template <class T>
T& Log_ptr<T>::operator=(const Log_ptr& InputLogPtr)
{
    this->__CleanUP__();
    this->ObjectPtr = InputLogPtr.ObjectPtr;
    this->RefCount = InputLogPtr.RefCount;
    std::cout << "At " << std::chrono::system_clock::now() << ", LogPtr was Assigned of, " << GetName() << " at " << ObjectPtr << std::endl;
}

template <class T>
T* Log_ptr<T>::operator->()
{
    std::cout << "At " << std::chrono::system_clock::now() << ", " << GetName() << " -> " << ObjectPtr << std::endl;
    return ObjectPtr;
}

template <class T>
T& Log_ptr<T>::operator*()
{
    std::cout << "At " << std::chrono::system_clock::now() << ", " << GetName() << " * " << ObjectPtr << std::endl;
    return *ObjectPtr;
}

template <class T>
std::string Log_ptr<T>::GetName()
{
    return ObjectPtr->name;
}

template <class T>
T* Log_ptr<T>::GetObjectPtr()
{
    return ObjectPtr;
}

template <class T>
void Log_ptr<T>::__CleanUp__()
{
    (*RefCount)--;
    if (*RefCount == 0)
    {
        if (ObjectPtr != nullptr)
        {
            std::cout << "Ref Count Reached Zero" << std::endl;
            delete ObjectPtr;
            delete RefCount;
        }
    }
}