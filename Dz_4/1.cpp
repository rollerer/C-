#include <iostream>
#include <list>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

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
void fu(int* a)
{
    a[1] = 0;
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

/*int* sort_con(int* a,int beg, int end)
{
    if(end-beg == 1)
    {
        return a;
    }
    int mid = int((end+beg)/2);
    int c[end-beg];
    std::cout<<beg<<'\n';
    int* b_1 = sort_con(a, beg, mid);
    int* b_2 = sort_con(a, mid, end);
    int i = 0;
    int j = 0;
    int k = 0;
    while(i<mid-beg and j<end-mid)
    {   
        if(b_1[i]<b_2[j])
        {
            c[k] = b_1[i];
            i++;
            k++;
        }
        else
        {
            c[k] = b_2[j];
            j++;
            k++;
        }
    }
    while(i<mid-beg)
    {
        c[k] = b_1[i];
        i++;
        k++;
    }
    while(j<end-mid)
    {
        c[k] = b_2[j];
        j++;
        k++;
    }
    return c;
}*/

template <typename T>
T sort_con(T a)
{
    if(a.size() == 1)
    {
        return a;
    }
    int mid = int(a.size()/2);
    T c;
    T f(a.begin(), a.begin()+mid);
    T d(a.begin()+mid, a.end());
    T b_1 = sort_con(f);
    T b_2 = sort_con(d);
    int i = 0;
    int j = 0;
    while(i<b_1.size() and j<b_2.size())
    {   
        if(b_1[i]<b_2[j])
        {
            c.push_back(b_1[i]);
            i++;
        }
        else
        {
            c.push_back(b_2[j]);
            j++;
        }
    }
    while(i<b_1.size())
    {
        c.push_back(b_1[i]);
        i++;
    }
    while(j<b_2.size())
    {
        c.push_back(b_2[j]);
        j++;
    }
    return c;
}

template <typename T>
T sort_vst(T a)
{
    T u;
    while(!a.empty())
    {
        int m = *std::min_element(a.begin(), a.end());
        u.push_back(m);
        a.erase(std::find(a.begin(), a.end(), m));
    }
    return u;
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
    //sort_con(m, 0, size);
    auto start_con = std::chrono::high_resolution_clock::now();
    std::vector<int> g = sort_con(numbers_1000);
    auto end_con = std::chrono::high_resolution_clock::now();

    auto duration_con = std::chrono::duration_cast<std::chrono::microseconds>(end_con - start_con);

    auto start_vst= std::chrono::high_resolution_clock::now();
    std::vector<int> k = sort_vst(numbers_1000);
    auto end_vst = std::chrono::high_resolution_clock::now();

    auto duration_vst = std::chrono::duration_cast<std::chrono::microseconds>(end_vst - start_vst);

    auto start_puz = std::chrono::high_resolution_clock::now();
    sort_puz(m, size);
    auto end_puz = std::chrono::high_resolution_clock::now();

    auto duration_puz = std::chrono::duration_cast<std::chrono::microseconds>(end_puz - start_puz);

    auto start_fast = std::chrono::high_resolution_clock::now();
    sort_fast(n, 0, size);
    auto end_fast = std::chrono::high_resolution_clock::now();

    auto duration_fast = std::chrono::duration_cast<std::chrono::microseconds>(end_fast - start_fast);

    std::cout<<"Быстрая: "<<duration_fast.count()<<'\n';
    std::cout<<"Пузырьковая: "<<duration_puz.count()<<'\n';
    std::cout<<"Слияние: "<<duration_con.count()<<'\n';
    std::cout<<"Вставки: "<<duration_vst.count()<<'\n';
    

    return 0;
}