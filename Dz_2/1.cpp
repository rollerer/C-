#include <iostream>
#include <deque>

//класс очереди
class DQ
{
    std::deque<std::string*>m;
    public:
    DQ()
    {
        m = {};
    }
    //вывод информации
    void show()
    {   
        std::cout<<"Количество заданий: "<<m.size()<<'\n';
        std::cout<<"Задания: "<<'\n';
        for(const std::string* i : m)
        {
            std::cout<<i[0]<<" "<<i[1]<<'\n';
        }
    }
    //добавление задания
    void add(std::string* a)
    {
        if(a[1] == "1" or a[1] == "high" or a[1] == "высокий")
        {
            m.emplace_front(a);
        }
        else if(a[1] == "0" or a[1] == "low" or a[1] == "низкий")
        {
            m.emplace_back(a);
        }
    }
    //выполнить задание
    void use(std::string pr)
    {   
        if(m.size())
        {
            if(pr == "1")
            {   
                std::cout<<*m.cbegin()[0]<<'\n';
                m.pop_front();
            }
            else
            {
                std::cout<<*m.cbegin()[m.size()-1]<<'\n';
                m.pop_back();
            }
        }
        else
        {
            std::cout<<"В очереди нет задач"<<'\n';
        }
    }

};

int main()
{
    DQ dq = DQ();
    std::deque<std::string*>m;
    std::string check;
    std::string prior;
    std::string comand;
    while(comand != "stop")
    {   
        std::cout<<"Выбери дейчтвие: добавить задание(add); выполнить задание высокого приоритета(1), низкого(0); узнать информацию о заданиях(inf)"<<'\n';
        std::cin>>comand;
        if(comand == "add")
        {
            std::cout<<"Напиши задачу и её приоритет, через пробел"<<'\n';
            std::cin>>check>>prior;
            dq.add(new std::string[2]{check, prior});
        }
        else if(comand == "inf")
        {
            dq.show();
        }
        else
        {
            dq.use(comand);
        }
    }
}