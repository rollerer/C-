#include <iostream>
#include <vector>
#include <list>

class HTable
{   
    std::vector<std::list<int>*> table;
    int size;
    public:
    // конструктор
    HTable(int siz)
    {
        size = siz;
        for(int i =0; i<size; i++)
        {   
            std::list<int>* a = new std::list<int>;
            table.push_back(a);
        }
    }
    //вывод хеш-таблицы
    void inf()
    {
        std::cout<<"length: "<<size<<'\n';
        for(int i = 0; i < size;i++)
        {   
            std::cout<<i<<'\n';
            for(int j : *table[i])
            {
                std::cout<<j<<", ";
            }
            std::cout<<'\n';
        }
    }
    //хеш-функция
    int hesh_fun(int a)
    {
        return (a*abs(a-1)+a*abs(a-2))%size;
    }
    //функция добавления элемента
    void add(int a)
    {
        table[hesh_fun(a)]->push_back(a);
    }
    //функция, которая показывает заполненость каждого остатка
    void fil()
    {
        for(int i = 0; i < size;i++)
        {
            std::cout<<i<<": "<<table[i]->size()<<'\n';
        }
    }
    //функция удаления
    void del(int a)
    {   
        int num = hesh_fun(a);
        auto it = table[num]->cbegin();
        while(it!=table[num]->cend())
        {
            if(*it == a)
            {
                table[num]->erase(it);
                break;
            }
            else
            {
                it++;
            }
        }
    }
    //функция поиска
    int find(int a)
    {
        int num = hesh_fun(a);
        auto it = table[num]->cbegin();
        while(it!=table[num]->cend())
        {
            if(*it == a)
            {
                return 1;
            }
            else
            {
                it++;
            }
        }
        return 0;
    }
};

int main()
{
    HTable t = HTable(101);
    for(int i = 0; i<1234; i++)
    {
        t.add(i);
    }
    //проверка работы функций
    t.fil();
    std::cout<<t.find(123)<<'\n';
    t.del(123);
    std::cout<<t.find(123)<<'\n';
}