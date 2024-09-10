#include <iostream>
#include <string>

int main() {    
    int amount;
    std::string text;
    std::cout<<"What do you want to write?";
    std::cin >> text;
    std::cout<<"How many times do you want to write it?";
    std::cin >> amount;
    for(int g = amount; g>0; g--){
        std::cout<<text<<std::endl;
        }
    return 0;
}