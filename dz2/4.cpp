#include <iostream>
#include <string>
main() {
    std::string big_str, small_str;
    std::cin>>big_str;
    std::cin>>small_str;
    int j;
    int col;
    col=0;
    for(int i = 0; i<big_str.length();i++){
        j=0;
        while (big_str[i+j]==small_str[j]){
            j++;
            if (j==small_str.length()){
                col++;                
            }
        }
    }
    std::cout<<col<<std::endl;
    return 0;
}