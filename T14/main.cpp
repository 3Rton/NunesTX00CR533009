#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>

class Big_Data 
{
public:

    void* pData;
    size_t pSize;

    Big_Data()
    {
        pData = std::malloc(1000);
        pSize = 1000;
    }

    Big_Data(int i)
    {
        pData = std::malloc(i);
        pSize = i;
    }

    Big_Data(const Big_Data& bd)
    {
        pData = std::malloc(sizeof(bd.pData));
        pSize = bd.pSize;
    }

    Big_Data(Big_Data&& obj)
    {
        pData = &obj.pData;
        pSize = std::move(obj.pSize);

        obj.pData = nullptr;
        obj.pSize = 0;
    }

    Big_Data operator=(Big_Data const& obj)
    {
        if (obj.pSize != pSize)
        {
            pData = std::realloc(pData, obj.pSize );
            pSize = obj.pSize;
        } 
        else
        {
            pData = obj.pData;
            pSize = obj.pSize;
        }

    }

    Big_Data& operator=(Big_Data&& obj)
    {
        if (obj.pSize != pSize)
        {
            pData = std::realloc(pData, obj.pSize );
            pData = &obj.pData;
            pSize = std::move(obj.pSize);
        } 
        else
        {
            pData = &obj.pData;
            pSize = obj.pSize;
        }

        obj.pData = nullptr;
        obj.pSize = 0;

        return *this;
    }
};


int main()
{
    
    Big_Data myData(1056);
    Big_Data ccData(myData);
    Big_Data assignData = ccData;

    std::cout << "Value of myData: " << myData.pSize << std::endl;
    std::cout << "Value of ccData: " << ccData.pSize << std::endl;
    std::cout << "Value of ccData: " << assignData.pSize << std::endl;

    Big_Data moveSemantic(myData);
    Big_Data moveConstructor = std::move(myData);

    std::cout << "Value of myData: " << myData.pSize << std::endl;
    std::cout << "Value of moveConstructor: " << myData.pSize << std::endl;

    moveSemantic = std::move(moveConstructor);

    std::cout << "Value of moveConstructor: " << moveConstructor.pSize << std::endl;
    std::cout << "Value of moveSemantic: " << moveSemantic.pSize << std::endl;

    return 0;
}
