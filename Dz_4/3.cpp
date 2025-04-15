#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

void move(int* a, int size, int place, int number, int start, int end)
{   
    int t = 0;
    if(start!= 0 and place-start < end-place)
    {
        for(int i = start ; i < place+1; i++)
        {
            a[i-1] = a[i];
        }
    }
    else
    {
        for(int i = end ; i > place-1; i--)
        {
            a[i+1] = a[i];
        }
    }
    a[place] = number;
}   
void show(int* a, int size)
{
    for(int i = 0; i<size; i++)
    {
        std::cout<<a[i]<<" ";
    }
    std::cout<<'\n';
}

int* sort_vst(int* a, int size)
{   
    int start = int(size/2);
    int end = int(size/2 + 1);
    int* b = new int[size]();
    int n = 1;
    int num = 0; 
    b[start] = a[0];
    while(end-start < size)
    {
        num = a[n];
        int place = 0;
        if(start!=0)
        {
            place = start-1;
        }
        for(int i = start; i<end+1; i++)
        {
            if(num<b[i])
            {
                break;
            }
            place ++;
        }
        move(b, size, place, num, start, end);
        if(start>0 and place-start<end-place)
        {
            start--;
        }
        else
        {
            end++;
        }
        n++;
    }
    return b;
}

int* sort_fast(int* a, int i, int j)
{   
    int beg = i;
    int end = j;
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
        return a;
    }
    if(j>beg)
    {   
        sort_fast(a, beg, j);
    }
    if(i<end)
    {   
        sort_fast(a, i, end);
    }
    return a;
}

int* sort_mix(int*a, int size)
{
    if(size<10)
    {
        return sort_vst(a, size);
    }
    else
    {
        return sort_fast(a, 0, size-1);
    }
}


int main()
{
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 1000);
    int size = 10;
    int s = 1000;
    int* m = new int[size]();
    int* n = new int[size]();
    for (int i = 0; i < size; i++) {
        int num = dist(gen);
        n[i] = num;
        m[i] = num;
    }
    int** k = new int*[s]();
    //так как время одной сортировки мало, то я сделал её 1000 раз подряд
    for(int i=0; i<s; i++)
    {   
        k[i] = new int[size];
        for(int j = 0; j< size; j++)
        {   
            k[i][j]=m[j];
        }
    }
    //измерение времени выполнения
    auto start_vst = std::chrono::high_resolution_clock::now();
    for(int i = 0; i< s; i++)
    {
        sort_vst(k[i], size);
    }
    auto end_vst = std::chrono::high_resolution_clock::now();

    auto duration_vst = std::chrono::duration_cast<std::chrono::microseconds>(end_vst - start_vst);


    
    auto start_fast = std::chrono::high_resolution_clock::now();
    
    for(int i = 0; i< s; i++)
    {
        sort_fast(k[i], 0, size-1);
    }
    auto end_fast = std::chrono::high_resolution_clock::now();

    auto duration_fast = std::chrono::duration_cast<std::chrono::microseconds>(end_fast - start_fast);
    
    std::cout<<"Быстрая: "<<duration_fast.count()<<'\n';
    std::cout<<"Вставки: "<<duration_vst.count()<<'\n';
}