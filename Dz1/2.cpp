#include <iostream>
#include <vector>

//функция печати
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
//перегрузка по умолчанию
template <typename T>
void Print( const T& a)
{   
    int ind = 0;
    for(const auto& i : a)
    {      
        std::cout<<i;
        if(ind < a.size()-1)
        { 
            std::cout<<","<<" ";
        }
        ind++;
    }
    std::cout<<'\n';
}

main()
{
    std::vector<int> data;
    std::vector<int> data_pos;
    std::vector<int> data_neg;
    int n = 0;
    std::cin>>n;
    int j = 0;
//ввод массива
    for(int i = 0; i<n; i++)
    {   
        std::cin>>j;
        data.push_back(j);
    }
//разделение и сортировка
    for(int i : data)
    {
//при положительных числах
        if (i>=0)
        {   
            if(data_pos.size() == 0)
            {
                data_pos.push_back(i);
            }
            else
            {
            int num = 0;
            while(data_pos[num]<i)
            {
                num++;
                if (num == data_pos.size())
                {
                    break;
                }
            }
            data_pos.emplace(data_pos.begin() + num, i);
            }
        }
//при отрицательных числах
        else
        {
            if(data_neg.size() == 0)
            {
                data_neg.push_back(i);
            }
            else
            {
            int num = 0;
            while(data_neg[num]<i)
            {
                num++;
                if (num == data_neg.size())
                {
                    break;
                }
            }
            data_neg.emplace(data_neg.begin() + num, i);
            }
        }
    }
//вывод
    Print(data_pos);
    Print(data_neg);
}