#include <iostream>
#include <vector>
#include <string>
#include <random>

#include <thread>
#include <mutex>

#include "GameplayStatics.h"
#include "GameTask.h"
#include "GTUpdateState.h"
#include "GTRender.h"
#include "TestHeader.h"


int main()
{

    //GTUpdateState* WorldState = new GTUpdateState();

    //WorldState->perform();

    //GTRender* renderer = new GTRender();

    TestHeader* newTest = new TestHeader();
    newTest->TestFunction();
    

}