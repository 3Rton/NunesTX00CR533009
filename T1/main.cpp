#include <iostream>
#include <vector>
#include <string>
#include <thread>

using namespace std;

void populateVector();
void SplitVector();
void SumPortion(unsigned long long int start, unsigned long long int len);

std::vector<int> LargeVector;
long long int sum;

int main()
{
    if (LargeVector.size() < 1) 
    {
        populateVector();
    }

    std::thread sv(SplitVector);

    sv.join();

    std::cout << "The sum of the large vectors elements was: " << sum << endl;

}

void populateVector() 
{
    LargeVector.reserve(100000);

    for (int i = 0; i < 100000; i++)
    {
        LargeVector.push_back(i);
    }
    
}

void SplitVector()
{
    int chunks = LargeVector.size() / 4;

    std::thread first(SumPortion, 0, 25000);
    std::thread second(SumPortion, 25000, 50000);
    std::thread third(SumPortion, 50000, 75000); 
    //std::thread fourth(SumPortion, 75000, 100000);

    first.join();
    second.join();
    third.join();
    //fourth.join();
}

void SumPortion(unsigned long long int start, unsigned long long int len)
{
    unsigned long long int val = 0;
    for(unsigned long long int i = start; i <= len; i++)
    {
        val += LargeVector.at(i);
    }

    sum += val;
}