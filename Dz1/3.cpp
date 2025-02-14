#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
#include <vector>

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
int find_max(int* a, int size)
{   
    int max = 0;
    int num = 0;
    for(int i = 0; i<size; i++)
    {
        if(a[i] > max)
        {
            max = a[i];
            num = i;
        }
    }
    return num;
}

main()
{
    std::ifstream file("file.txt");
    std::string s;
    std::string f;
    std::set<std::string> dif_words;
    std::vector<std::string> all_words;
    while(std::getline(file, s))
    {
        std::stringstream str(s);
        while(str>>f)
        {   
            dif_words.insert(f);
            all_words.push_back(f);
        }
    }
    int* amount = new int[dif_words.size()];
    for(int i = 0; i<dif_words.size(); i++)
    {
        amount[i] = 0;
    }
    int num = 0;
    for(std::string i : dif_words)
    {
        for(std::string j : all_words)
        {
            if (i==j)
            {
                amount[num]++;  
            }
        }
        num++;
    }
    int num_max = find_max(amount, dif_words.size());
    std::set<std::string>::iterator it = dif_words.begin();
    for (int i = 0; i<num_max; i++)
    {
        it++;
    }
    std::cout<<"Самое частое слово: "<<*it<<'\n';
    std::cout<<"Оно повторялось "<<amount[num_max]<<" раз";
}