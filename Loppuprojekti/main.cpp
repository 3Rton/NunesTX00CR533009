#include <iostream>

#include <raylib-cpp.hpp>

int main(int, char**){
    std::cout << "Hello, from Loppuprojekti!\n";

    raylib::AudioDevice ad(false);
    
    
    std::cout << "OOP Audio device init: " << std::boolalpha << ad.IsReady();
}
