#include <iostream>
#include <cmath>

main() {
    int number;
    std::cin>>number;
    int d = 2;
    double n = sqrt(number);
    while(d<=n){
        if (number%d){
            std::cout<<number/d;
            return 0;
    } 
    d++;
}   
    std::cout<<number%5<<std::endl;
    std::cout<<"Prostoye";
    return 0;
}