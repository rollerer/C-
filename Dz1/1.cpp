#include <iostream>
#include <vector>
#include <set>

template <typename T>
void Print( const T& a, std::string n)
{   
    int ind = 0;
    for(const auto& i : a)
    {      
        std::cout<<i;
        if(ind < a.size()-1)
        {
            std::cout<<n<<" ";
        }
        ind++;
    }
    std::cout<<'\n';
}

main()
{
    std::vector<int> data = {1,2,3};
    std::set<std::string> data_2 = {"a", "b", "c"};
    Print(data_2, ",");
    Print(data, ";");
}