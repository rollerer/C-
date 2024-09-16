#include <iostream>

main() {
    int a;
    int sum;
    std::cin>>a;
    while (a!=0){
        if (a>0){
            sum+=a;
        }
        std::cout<<sum<<std::endl;
        std::cin>>a;
    }
    std::cout<<sum;
    return 0;
}