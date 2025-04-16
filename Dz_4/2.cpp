#include <iostream>
#include <list>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
#include <memory>


int* sort_puz_(int* a,  int size)
{   
    int i = 0;
    int flag = 1;
    int f = 0;
    int t = 0;
    while(flag)
    {
        if(a[i] > a[i+1])
        {
            t = a[i];
            a[i] = a[i+1];
            a[i+1] = t;
            if(i>0)
            {
                if(a[i]<a[i-1])
                {
                    f = 1;
                }
            }
            if(i<size-2)
            {
                if(a[i+1]>a[i+2])
                {
                    f = 1;
                }
            }
        }
        i++;
        if(i == size-1)
        {
            i = 0;
            if(f == 0)
            {
                flag = 0;
            }
            f = 0;
        }
    }
    
    return a;
}

int* sort_puz(int* a,  int size)
{   
    int i = 0;
    int flag = 1;
    int f = 0;
    int t = 0;
    while(flag)
    {
        if(a[i] > a[i+1])
        {
            t = a[i];
            a[i] = a[i+1];
            a[i+1] = t;
            f = 1;
        }
        i++;
        if(i == size-1)
        {
            i = 0;
            
            if(f == 0)
            {
                flag = 0;
            }
            f = 0;
        }
    }
    
    return a;
}

int main()
{
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 1000);
    std::vector<int> numbers_1000;
    int size = 10000;
    int* m = new int[size];
    int* n = new int[size];
    for (int i = 0; i < size; i++) {
        int num = dist(gen);
        numbers_1000.push_back(num);
        m[i] = num;
        n[i] = num;
    }
    auto start_puz_ = std::chrono::high_resolution_clock::now();
    sort_puz_(m, size);
    auto end_puz_ = std::chrono::high_resolution_clock::now();

    auto duration_puz_ = std::chrono::duration_cast<std::chrono::microseconds>(end_puz_ - start_puz_);

    auto start_puz = std::chrono::high_resolution_clock::now();
    sort_puz(n, size);
    auto end_puz = std::chrono::high_resolution_clock::now();

    auto duration_puz = std::chrono::duration_cast<std::chrono::microseconds>(end_puz - start_puz);

    std::cout<<"Пузырьковая_: "<<duration_puz_.count()<<'\n';
    std::cout<<"Пузырьковая: "<<duration_puz.count()<<'\n';

}