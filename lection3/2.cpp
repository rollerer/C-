#include <iostream>

struct FIO
{
    std::string name;
    std::string sername;
};

struct BOOK
{
    std::string name = "Unknown";
    struct FIO fio {"Unknown", "Unknown"};
    int year = 0;
    int num_pages = 0;
    void display_book()
    {
        std::cout<<"Name: "<<name<<'\n';
        std::cout<<"FIO: "<<fio.name<<" "<<fio.sername<<'\n';
        std::cout<<"Year: "<<year<<'\n';
        std::cout<<"Pages: "<<num_pages<<'\n';
    }

};

struct BOOK create_book(std::string name, std::string Name, std::string Sername, int year, int num_pages)
{
    struct BOOK a;
    a.name = name;
    a.year = year;
    a.num_pages = num_pages;
    a.fio.name = Name;
    a.fio.sername = Sername;
    return a; 
}

main()
{   
    int N;
    printf("Write amount of books.\n");
    std::cin>>N;
    struct BOOK library[N];
    for(int i = 0; i<N; i++)
    {   
        std::string s;
        printf("Default(D) or Custom(C)?\n");
        std::cin>>s;
        if(s == "D")
        {
            struct BOOK def;
            library[i] = def;
        }
        else if(s == "C")
        {   
            std::string name;
            std::string Name;
            std::string Sername;
            int year;
            int num_pages;
            printf("Name of book:\n");
            std::cin>>name;
            printf("FIO of author:\n");
            std::cin>>Name>>Sername;
            printf("Year:\n");
            std::cin>>year;
            printf("Number of pages\n");
            std::cin>>num_pages;
            struct BOOK cus = create_book(name, Name, Sername, year, num_pages);
            library[i] = cus;
        }
        else
        {
            printf("Wrong input.\n");
        }
    }
    for(int i = 0; i<N; i++)
    {
        printf("\n");
        library[i].display_book();
    }
}
