#include <iostream>

class Time
{
private:
    int hours{};
    int minutes{};
    int seconds{};
public:
    void print()
    {
        std::cout<<hours<<" : "<<minutes<< " : "<<seconds<<'\n';
    };
    Time(int h, int m, int s)
    {
        hours = h;
        minutes = m;
        seconds = s;
    };
};

class Student
{
private:
    const std::string Name = "Vasya";
    const std::string Sername = "Pupkin";
    std::string Group{};
    int Age{};
    int mental_health{};
    int Progress{};
    int energy{};
    float time_student{};
    int money{};

public:
void print()
{   
    std::cout<<'\n';
    std::cout<<"Name: "<<Name<<'\n';
    std::cout<<"Sername: "<<Sername<<'\n';
    std::cout<<"Age: "<<Age<<'\n';
    std::cout<<"Group: "<<Group<<'\n';
    std::cout<<"Progress: "<<Progress<<'\n';
    std::cout<<"Mental health: "<<mental_health<<'\n';
    std::cout<<"Energy: "<<energy<<'\n';
    std::cout<<"Student's time: "<<time_student<<" hours"<<'\n';
    std::cout<<"Money: "<<money<<'\n';
};
    float show_time()
    {
        return time_student;
    }
    int show_energy()
    {
        return energy;
    }
    int show_mental()
    {
        return mental_health;
    }
    int show_progress()
    {
        return Progress;
    }
    Student(std::string G, int a)
    {
        Group = G;
        Age = a;
        mental_health = 100;
        energy = 100;
        Progress = 0;
        time_student = 24*7;
        money = 0;
    };
    Student(std::string G) : Student(G, 19) {}
    void Eat()
    {
        if(money>20, time_student>0.4)
        {
            money -= 20;
            energy += 20;
            time_student -= 0.4;
        }
        else
        {
            std::cout<<"erroe\n";
        }        
    }
    void Sleep(int t)
    {   
        if(time_student > t)
        {
            energy += t*10;
            mental_health += t*5;
            time_student -= t;
        }
        else
        {
            std::cout<<"erroe\n";
        }      
    }
    void Botay(int t)
    {   
        if(energy>t*4, mental_health>t*10, time_student>t)
        {
            energy -= t*4;
            mental_health -= t*10;
            time_student -= t;
            Progress += t*10;
        }
        else
        {
            std::cout<<"erroe\n";
        }        
    }
    void Work(int t)
    {   
        if(energy > t*4, mental_health > t*10, time_student > t)
        {
            energy -= t*4;
            mental_health -= t*10;
            time_student -= t;
            money += t*50;
        }        
        else
        {
            std::cout<<"erroe\n";
        }
    }
    void Relax(int t)
    {       
        if(time_student > t)
        {
            mental_health += t*5;
            time_student -= t;
        }
        else
        {
            std::cout<<"erroe\n";
        }    
    }
};

main()
{   
    printf("Write your group and age (B01-100 20)\n");
    std::string gr;
    int age;
    std::cin>>gr>>age;
    Student a(gr, age);
    a.print();
    printf("You have one week (24*7 hours) to solve homework\n");
    printf("You can eat(write eat), sleep(write sleep time(float in hours)),\nwork(write work time(float in hours)), botat(write botay time(float in hours)),\nrelax(write relax time(float in hours)), if you want to see information write inf\n");
    float t = a.show_time();
    int en = a.show_energy();
    int ment = a.show_mental();
    int prog = a.show_progress();
    std::string action;
    while (t>0)
    {   
        std::cin>>action;
        if(action == "eat")
        {
            a.Eat();
        }
        else if(action == "inf")
        {
            a.print();
        }
        else
        {
            float tim;
            std::cin>>tim;
            if(action == "sleep")
            {
                a.Sleep(tim);
            }
            else if(action == "work")
            {
                a.Work(tim);
            }
            else if(action == "botay")
            {
                a.Botay(tim);
            }
            else if(action == "relax")
            {
                a.Relax(tim);
            }
            else
            {
                printf("Wrong input");
            }
        }
        en = a.show_energy();
        ment = a.show_mental();
        t = a.show_time();
        prog = a.show_progress();
        if(en<=0)
        {
            printf("Ty skis...\n");
            break;
        }
        if(ment<=0)
        {
            printf("\nTy stoish na krishe KPM, s golovy sorval veter tvoy kolpak...\n");
            break;
        }
        if(prog >= 100)
        {
            break;
        }
    }
    
    if (prog<100, ment>0)
    {
        printf("Tebya chislanuli(\n");
    }
    else if (prog>=100)
    {
        printf("Pozdravlyau, ty sdal 1 iz 8 domashek\n");
    }    
}