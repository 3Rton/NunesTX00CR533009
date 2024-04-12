#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <cstdlib>


int main()
{
    /*
    Some reasons not to use exceptions would be:
    -They are expensive (uses heap, stack unwinding, uses RTTI, implementation defined deallocation)
    -They can lead to very cluttered and ugly code
    -Cognitively expensive (trying to think of every case and program to catch them)
    -Make API design less clear and more confusing to use

    Honestly, there didnt seem to be that many reasons to use them. Ensuring mission critical code doesnt crash seemed like one.
    Handling "expected" exceptions seemed like another. Logging warnings. Peter Muldoon scopes their usage to error tracing,
    stack unwinding, and data passing/control flow (when you have to)
    */


    return 0;
}
