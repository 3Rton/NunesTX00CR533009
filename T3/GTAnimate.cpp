#include "GTAnimate.hpp"


GTAnimate::GTAnimate() {}

GTAnimate::~GTAnimate() {}

void GTAnimate::perform()
{
    Timer* tt = new Timer();
    tt->StartTimer();
    for(int i = 0; i < 5000000; i++)
    {
        double a = 1000 * 100000;
    }
    std::cout << "Current Animation Advanced" << std::endl;
    tt->StopTimer("GTAnimate::Perform ");
}