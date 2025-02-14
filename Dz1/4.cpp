#include <iostream>
#include <stack>
#include <sstream>
#include <fstream>

bool check(std::string a, std::stack<std::string>* T)
{
    if (a == ")")
    {   
        if (T->top() == "(")
        {
            T->pop();
        }
        else
        {
            return false;
        }
    }
    else if(a == "}")
    {
        if (T->top() == "{")
        {
            T->pop();
        }
        else
        {
            return false;
        }
    }
    else if(a == "]")
    {
        if (T->top() == "[")
        {
            T->pop();
        }
        else
        {
            return false;
        }
    }
    else
    {
        T->push(a);
    }
    return true;

}
main()
{
    std::ifstream file("scob.txt");
    std::string s;
    std::string f;
    int flag = 1;
    while(std::getline(file, s))
    {   
        std::stringstream str(s);
        while(str>>f)
        {   
            flag = 1;
            std::stack<std::string> scob;
            int i = 0;
            while(f[i])
            {
                if(!check(std::string(1, f[i]), &scob))
                {
                    flag = 0;
                }
                i++;
            }
            if(flag)
            {
                std::cout<<"правильная\n";
            }
            else
            {
                std::cout<<"неправильная\n";
            }
        }
    }
}