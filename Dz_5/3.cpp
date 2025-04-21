#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <random>
#include <future>

void sort(std::vector<int>* vec, int num, int count)
{
    std::sort(vec->begin()+num*vec->size()/count, vec->begin()+(num+1)*vec->size()/count);
}

auto find(std::vector<int>* vec, int number, int num, int count)
{
    auto it = vec->begin()+num*vec->size()/count;
    while(it!=vec->begin()+(num+1)*vec->size()/count)
    {
        if(*it != number)
        {
            it++;
        }
        else
        {
            return it;
        }
    }
    return vec->end();
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

    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 1000);
    int size = 10000;
    std::vector<int> vec;
    for (int i = 0; i < size; i++) {
        int num = dist(gen);
        vec.push_back(num);
    }
    int all = size/500;
    std::vector<std::future<std::vector<int>::iterator>> futures;
    for(int i = 0; i < all; i++)
    {
        futures.push_back(std::async(std::launch::async, find, &vec, 250, i, all));
    }
    auto find = vec.end();
    for (auto& fut : futures) {
        find = fut.get();
        if(find != vec.end())
        {
            break;
        }
    }
    std::cout<<*find<<'\n';
    std::vector<std::thread> threads;
    for(int i = 0; i < all; i++)
    {
        threads.emplace_back(sort, &vec, i, all);
    }
    for (auto& t : threads)
    {
        t.join();
    }   
    std::sort(vec.begin(), vec.end());
}