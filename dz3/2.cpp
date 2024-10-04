#include <iostream>
#define N 5


//функция поиска int
void get (int n, int *m)
{
    int flag;
    for(int i = 0; i<N; i++)
    {
        if(m[i]==n)
        {
            std::cout<<"found";
            flag = 1;
        }
    }
    if(flag != 1)
    {
        std::cout<<"not found";
    }
}
//функция поиска float
void get (float n, float *m)
{
    int flag;
    for(int i = 0; i<N; i++)
    {
        if(m[i]==n)
        {
            std::cout<<"found";
            flag = 1;
        }
    }
    if(flag != 1)
    {
        std::cout<<"not found";
    }
}
//функция поиска char
void get (char n, char *m)
{
    int flag;
    for(int i = 0; i<N; i++)
    {
        if(m[i]==n)
        {
            std::cout<<"found";
            flag = 1;
        }
    }
    if(flag != 1)
    {
        std::cout<<"not found";
    }
}

main()
{   
    std::cout<<"Write type of data"<<'\n';
    std::string str;
    std::cin>>str;
    std::cout<<"Write "<<N<<" elemnets of massive"<<'\n';
    // поиск в массиве int
    if (str == "int")
    {  
        int mas[N];
        for (int i = 0; i<N;i++)
        {
            std::cin>>mas[i];
        }
        int *m = mas;
        int n;
        std::cin>>n;
        get(n, m);
    }
    //поиск в массиве float
    else if (str == "float")
    {   
        float mas[N];
        for (int i = 0; i<N;i++)
        {
            std::cin>>mas[i];
        }
        float *m = mas;
        float n;
        std::cin>>n;
        get(n, m);
    }
    //поиск в массиве char
    else if (str == "char")
    {   
        char mas[N];
        for (int i = 0; i<N;i++)
        {
            std::cin>>mas[i];
        }
        char *m = mas;
        char n;
        std::cin>>n;
        get (n, m);
    }
    else
    {
        std::cout<<"Wrong input";
    }
    
    
}
