#include "GTRender.hpp"


GTRender::GTRender() {}

GTRender::~GTRender() {}

void GTRender::perform()
{
    Timer* tt = new Timer();
    tt->StartTimer();
    for(int i = 0; i < 5000000; i++)
    {
        double a = 1000 * 100000;
    }
    std::cout << "Current Fragment Rendered" << std::endl;
    tt->StopTimer("GTRender::Perform ");
}