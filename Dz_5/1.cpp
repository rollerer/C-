#include <iostream>
#include <thread>
#include <vector>
void print(int count)
{
    std::cout<<"Id: "<<std::this_thread::get_id()<<'\n';
    std::cout<<"Количество: "<<count<<'\n';
    std::cout<<"Hello world\n";
}

int main()
{   
    int all = 5;
    std::vector<std::thread> threads;

    for(int i = 0; i < all; i++)
    {
        threads.emplace_back(print, all);
    }
    for (auto& t : threads)
    {
        t.join();
    }
}