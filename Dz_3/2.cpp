#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>

template <typename T>
std::map<std::string, int> deep(std::map<std::string, T> m, std::map<std::string, int> nam, std::string name)
{   
    if(m.find(name) != m.cend())
    {
        for(std::string i : m[name])
        {
            nam[i] = nam[name] + 1;
            nam = deep(m, nam, i);
        }
    }
    return nam;
}

int main()
{
    std::ifstream file("file.txt");
    std::string s;
    std::string child;
    std::string parent;
    std::set<std::string> par;
    std::set<std::string> chi;
    std::map<std::string, std::vector<std::string>> tree;
    std::map<std::string, int> answ;
    std::getline(file, s);
    while(std::getline(file, s))
    {   
        std::stringstream string(s);
        string>>child;
        string>>parent;
        tree[parent].push_back(child);
        par.insert(parent);
        chi.insert(child);
        for(std::string i : chi)
        {
            par.erase(i);
        }
    }
    answ[*par.begin()] = 0;
    answ = deep(tree, answ, *par.begin());
    for(const auto& [name, dep] : answ)
    {
        std::cout<<name<<" "<<dep<<'\n';
    }
}