#include <iostream>
#include <vector>
#include <algorithm>

void decreaseHP(int &hp)
{
    hp = std::max(0, hp - 100);
}

class DecreaseHPObj
{
public:
    void operator()(int &hp) const
    {
        hp = std::max(0, hp - 100);
    }
};

void PrintHPs(std::vector<int> &Collection)
{
    for (int hp : Collection)
    {
        std::cout << hp << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> enemyHP = {800, 300, 125, 50, 450};

    // Using separate function
    std::for_each(enemyHP.begin(), enemyHP.end(), decreaseHP);

    PrintHPs(enemyHP);

    // Using function object
    std::for_each(enemyHP.begin(), enemyHP.end(), DecreaseHPObj());

    PrintHPs(enemyHP);

    // Using lambda function
    std::for_each(enemyHP.begin(), enemyHP.end(), [](int &hp)
                  { hp = std::max(0, hp - 100); });
    
    PrintHPs(enemyHP);

    // Using named lambda function
    auto decreaseLambda = [](int &hp)
    {
        hp = std::max(0, hp - 100);
    };
    std::for_each(enemyHP.begin(), enemyHP.end(), decreaseLambda);

    PrintHPs(enemyHP);

    // Sorting in descending order
    std::sort(enemyHP.begin(), enemyHP.end(), [](int a, int b)
              { return a > b; });

    PrintHPs(enemyHP);

    return 0;
}
