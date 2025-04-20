#include <iostream>
#include <thread>
#include <vector>

void fill(std::vector<int>* v, int num, int count)
{   
    
    for(int i = num*v->size()/count; i < (num+1)*v->size()/count; i++)
    {
        auto it = v->begin()+i;
        *it = num;
    }
}

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

int main()
{   
    int size = 10000;
    int all = size/5;
    std::vector<int> vec(size, 0);
    std::vector<std::thread> threads;

    for(int i = 0; i < all; i++)
    {
        threads.emplace_back(fill, &vec, i, all);
    }
    for (auto& t : threads)
    {
        t.join();
    }   
    Print(vec, ",");
}