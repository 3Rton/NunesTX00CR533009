#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#define subC

int main()
{
    std::string s1 {"Kissa"};
    std::string s2 {""};
    std::string s3 {"Koira"};

    std::vector<std::string> v;

    #if defined(subA)

    std::cout << "s1 origin: " << static_cast<void*>(s1.data() ) << " contains: " << s1 << std::endl;
    std::cout << "s2 origin: " << static_cast<void*>(s2.data() ) << " contains: " << s2 <<  std::endl;

    s1 = s2;

    std::cout << "s1 origin: " << static_cast<void*>(s1.data() ) << " contains: " << s1 << std::endl;
    std::cout << "s2 origin: " << static_cast<void*>(s2.data() ) << " contains: " << s2 <<  std::endl;

    //Content has been copied but pointers are different

    #elif defined(subB)

    std::cout << "s1 origin: " << static_cast<void*>(s1.data() ) << " contains: " << s1 << std::endl;
    std::cout << "s2 origin: " << static_cast<void*>(s2.data() ) << " contains: " << s2 <<  std::endl;

    s1 = std::move(s2);

    std::cout << "s1 origin: " << static_cast<void*>(s1.data() ) << " contains: " << s1 << std::endl;
    std::cout << "s2 origin: " << static_cast<void*>(s2.data() ) << " contains: " << s2 <<  std::endl;

    /*It seems, in fact, that strings are wrapped in buffers, and those buffers don't allow copying the pointers. 
    This explains why the pointer never matches
    */

    #elif defined(subC)

    v.push_back(s3);

    std::cout << "s3 " << s3 << std::endl;
    std::cout << "v-last " << v.back() <<  std::endl;

    v.push_back(std::move(s3) );

    std::cout << "s3 " << s3 << std::endl;
    std::cout << "v-last " << v.back() <<  std::endl;

    //s3 has lost its data

    #endif

    return 0;
}
