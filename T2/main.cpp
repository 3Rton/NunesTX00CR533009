#include <iostream>
#include <vector>
#include <string>
#include <random>

#include <thread>
#include <mutex>

class BankAccount
{
    public:
    double Balance;

    BankAccount() 
    {
        Balance = 100000.0;
    };
    ~BankAccount();

    void AddBalance(double inAmount)
    {
    Balance += inAmount;
    };

    void SubBalance(double outAmount)
    {
    Balance -= outAmount;
    };

};

void RandomOperations(BankAccount* access);

std::random_device rng;
std::mt19937 gen(rng());

std::mutex mtx;

int main()
{

    BankAccount* myBA = new BankAccount();

    std::thread t1(RandomOperations, myBA);
    std::thread t2(RandomOperations, myBA);
    
    t1.join();
    t2.join();


    std::cout << "Balance: " << myBA->Balance << std::endl;

}

void RandomOperations(BankAccount* access)
{
    std::uniform_int_distribution<> TypeDist(0, 1);
    std::uniform_int_distribution<> OpsDist(0, 100);
    std::uniform_real_distribution<> AmountDist(1, 6000);
    int NumOperations = OpsDist(gen);

    for(int i = 0; i < NumOperations; i++ )
    {
        const std::lock_guard<std::mutex> lock(mtx);
        int OpType = TypeDist(gen);
        if (OpType == 0) 
        {
            access->AddBalance( AmountDist(gen) );
        }
        if  (OpType == 1)
        {
            access->SubBalance( AmountDist(gen) );
        }
    }
};