#include <iostream>
#include <map>

class Phone
{
    std::map<std::string, std::string> m;
    public:
    Phone()
    {
        m = {};
    }
    void add(std::string a, std::string b)
    {
        m[a] = b;
    }
    void inf()
    {   
        if(m.size())
        {
            for(const auto& [name, number] : m)
            {
                std::cout<<"Имя: "<<name<<" \nНомер: "<< number<<'\n';
            }
        }
        else
        {
            std::cout<<"Список пуст\n";
        }
    }
    void find(std::string name)
    {
        auto it = m.find(name);
        if(it!=m.end())
        {
            std::cout<<"Имя: "<<it->first<<"\nНомер: "<<it->second<<'\n';
        }
        else
        {
            std::cout<<"Такого контакта нет\n";
        }
    }
    void del(std::string name)
    {
        if(!m.erase(name))
        {
            std::cout<<"Такого контакта нет\n";
        }
    }
};

int main()
{
    Phone phone = Phone();
    std::string comand;
    std::string name;
    std::string n;
    std::string number;
    while(comand != "stop")
    {   
        std::cout<<"Выбери дейчтвие: добавить/удалить контакт(add/del); вывести список контактов(inf); найти контак(find)"<<'\n';
        std::cin>>comand;
        if(comand == "add")
        {
            std::cout<<"Напиши имя и номер, через пробел"<<'\n';
            std::cin>>name>>number;
            phone.add(name, number);
        }
        else if(comand == "inf")
        {
            phone.inf();
        }
        else if(comand == "find")
        {   
            std::cout<<"Напиши имя контакта"<<'\n';
            std::cin>>n;
            phone.find(n);
        }
        else if(comand == "del")
        {   
            std::cout<<"Напиши имя контакта"<<'\n';
            std::cin>>n;
            phone.del(n);
        }
    }
}