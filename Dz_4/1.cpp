#include <iostream>
#include <list>
#include <random>
#include <vector>
#include <chrono>

template <typename T>

T sort_puz(T a)
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
        if(i == a.size()-1)
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
template <typename T>
void fu(T* b)
{
    std::vector<int>& a = *b;
    a[1] = 10;
}

template <typename T>
T* sort_fast(T* b, int i, int j)
{    
    int beg = i;
    int end = j;
    std::vector<int>& a = *b;

    //std::cout<<j<<'\n';
    int mid = a[int((end+beg)/2)];
    int t;
    int swap = 0;
    while(i<j)
    {
        while (a[i] < mid)
        {   
            i++;
        }
        while (a[j] > mid)
        {
            j--;
        }
        if(i<=j)
        {
            t = a[i];
            a[i] = a[j];
            a[j] = t;
            i++;
            j--;
        }
    }
    if(end-beg == 1)
    {
        return &a;
    }
    if(j>beg)
    {   
        sort_fast(&a, beg, j);
    }
    if(i<end)
    {   
        sort_fast(&a, i, end);
    }
    return &a;
}

int main()
{
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 1000);
    std::vector<int> numbers_1000;
    for (int i = 0; i < 10000; i++) {
        numbers_1000.push_back(dist(gen));
    }
    std::vector<int>* num = &numbers_1000;

    auto start_fast = std::chrono::high_resolution_clock::now();
    sort_fast(num, 0, numbers_1000.size()-1);
    auto end_fast = std::chrono::high_resolution_clock::now();

    auto duration_fast = std::chrono::duration_cast<std::chrono::microseconds>(end_fast - start_fast);

    auto start_puz = std::chrono::high_resolution_clock::now();
    sort_puz(numbers_1000);
    auto end_puz = std::chrono::high_resolution_clock::now();

    auto duration_puz = std::chrono::duration_cast<std::chrono::microseconds>(end_puz - start_puz);

    std::cout<<"Быстрая: "<<duration_fast.count()<<'\n';
    std::cout<<"Пузырьковая: "<<duration_puz.count()<<'\n';
    /*for (int num : *n) 
    {
        std::cout << num << " ";
    }*/
    return 0;
}