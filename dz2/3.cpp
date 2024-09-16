#include <iostream>
#include <cmath>
main(){
    int len;
    int sum;
    std::cin>>len;
    int* number = new int [len];
    for (int i = 0; i<len; i++){
        number[i] = i*i;
        sum+=number[i];
    }
    std::cout<<sum<<std::endl;
    delete[] number;
    return 0;
}