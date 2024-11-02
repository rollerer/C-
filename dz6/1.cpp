#include <iostream>

struct FIO{
    std::string Name = "Unknown";
    std::string Surname = "Unknown";
};

class Animals{
    public:
        virtual void sound() = 0;
};

class CATS: public Animals{
    private:
        int health;
        int age;
        std::string name;
        std::string poroda;
    public:
        void sound(){
            std::cout<<"Myau\n";
        }
        CATS(std::string name_, int age_, std::string poroda_){
            health = 100;
            name  = name_;
            age = age_;
            poroda = poroda_;
        }
        CATS()
        {
            health = 100;
            name  = "None";
            age = 0;
            poroda = "None";
        }
        void show_info(){
            std::cout<<"Name: "<<name<<'\n';
            std::cout<<"Age: "<<age<<'\n';
            std::cout<<"Poroda: "<<poroda<<'\n';
            std::cout<<"\n";
        }
        void show_hp(){
            std::cout<<health<<"\n";
        }
        friend class Vet;
};

class DOGS: public Animals
{
    private:
        int health;
        int age;
        std::string name;
        std::string poroda;
    public:
        void sound(){
            std::cout<<"GAF\n";
        }
        DOGS(std::string name_, int age_, std::string poroda_){
            health = 100;
            name  = name_;
            age = age_;
            poroda = poroda_;
        }
        DOGS()
        {
            health = 100;
            name  = "None";
            age = 0;
            poroda = "None";
        }
        void show_info(){
            std::cout<<"Name: "<<name<<'\n';
            std::cout<<"Age: "<<age<<'\n';
            std::cout<<"Poroda: "<<poroda<<'\n';
            std::cout<<"\n";
        }
        void show_hp(){
            std::cout<<health<<"\n";
        }
        friend class Vet;
};



class Hozyain{
    private:
        struct FIO fio;
        int age;
        int N_cat;
        int N_dog;
        DOGS dog;
        CATS** masive_of_cats;
    public:
        friend class Vet;
        Hozyain(std::string nn, std::string sn, int age__, int N_cat_, int N_dog_, DOGS d, CATS** c)
        {
            fio = FIO{nn, sn};
            age = age__;
            N_cat = N_cat_;
            N_dog = N_dog_;
            this->dog = d;
            masive_of_cats = c;
        }
    void show_info()
    {
        std::cout<<"Name: "<<fio.Name<<'\n';
        std::cout<<"Surame: "<<fio.Surname<<'\n';
        std::cout<<"Age: "<<age<<'\n';
        std::cout<<"Number of cats: "<<N_cat<<'\n';
        std::cout<<"Number of dogs "<<N_dog<<'\n';
        std::cout<<"Pets info: "<<'\n';
        std::cout<<'\n';
        std::cout<<"Dogs:\n";
        dog.show_info();
        std::cout<<"Cats:\n";
        for (int i = 0; i<N_cat; i++)
        {
            masive_of_cats[i]->show_info();
        }
    }

};

class Vet{
    FIO fio;
    public:
    Vet(std::string Name, std::string Surname)
    {
        fio = FIO{Name, Surname};
    }
    void medosmotr(Hozyain hoz)
    {   
        if (hoz.dog.health < 100)
        {
        hoz.dog.health += 10;
        }
        for (int i = 0; i<hoz.N_cat; i++)
        {   
            if (hoz.masive_of_cats[i]->health < 100)
            {
                hoz.masive_of_cats[i]->health += 10;
            }
        }
    }
    void speak_with_Hozyain(Hozyain hoz)
    {
        std::cout<<"I spoke with "<<hoz.fio.Name<<" "<< hoz.fio.Surname<<"\n";
    }

};


int main()
{   
    int N_c;
    int N_d;
    std::cout<<"How many cats do you have?\n";
    std::cin>>N_c;
    CATS* mas_c[N_c];
    for(int i = 0; i<N_c; i++)
    {   
        std::string n;
        int a;
        std::string p;
        std::cout<<"Enter the name of cat\n";
        std::cin>>n;
        std::cout<<"Enter the age of cat\n";
        std::cin>>a;
        std::cout<<"Enter the poroda of cat\n";
        std::cin>>p;
        mas_c[i] = new CATS(n, a, p);
    }
    std::cout<<"How many dogs do you have?\n";
    std::cin>>N_d;
    std::string n;
    int a;
    std::string p;
    std::cout<<"Enter the name of dog\n";
    std::cin>>n;
    std::cout<<"Enter the age of dog\n";
    std::cin>>a;
    std::cout<<"Enter the poroda of dog\n";
    std::cin>>p;
    CATS** mm = mas_c;
    DOGS dog = DOGS(n, a, p);
    Hozyain hoz = Hozyain("Ivan", "Petrovich", 23, N_c, N_d, dog, mm);
    hoz.show_info();
    Vet vet = Vet("Petr", "Ivanovich");
    vet.medosmotr(hoz);
    vet.speak_with_Hozyain(hoz);
}