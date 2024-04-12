#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <cstdlib>


int main()
{
    size_t cycles = 0;
    std::vector<size_t*> v;

    //Throws bad_alloc at 90811000 size_t's

    //Should you prepare for bad memory allocations? I probably depends on are you programming games, embedded systems, or a pacemaker
    //Peter Muldoon notes you should never use exceptions for memory exhaustion because stack winding is not guaranteed.

    while( true )
    {
        try
        {
            for (size_t i = 0; i < 10000; i++)
            {
            size_t* cycleInt = new size_t(10000000);
            v.push_back(cycleInt);
            cycles++;
            }
        }
        catch (std::bad_alloc& ba)
        {
            std::cout << "Bad Allocation occured at array size: " << v.size() << std::endl;
            std::cout << "Memory used: " << ( (v.size()*10000000) / pow(2, 20)) << "mb" << std::endl;
            break;
        }

        std::cout << "Cycle: " << cycles << std::endl;
        std::cout << "Array size: " << v.size() << std::endl;
    }
    
    return 0;
}
