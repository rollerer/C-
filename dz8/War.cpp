#include <iostream>
#include "Magic.cpp"
#include "Orks.cpp"

main()
{
    std::cout<<"How many Nature spells do you now?\n";    
    int N_NS;
    std::cin>>N_NS;
    NatureSpell* Ns[N_NS];
    int N;
    for (int i = 0; i< N_NS; i++)
    {
        std::cout<<"How many elements in nature spell?\n";
        std::cin>>N;
        Elements** m {new Elements*[N]};
        std::string ell;
        for(int i = 0; i<N; i ++)
        {   
            std::cout<<"Write "<<N<<" elements: fire (f), water (w), earth (e)\n";
            std::cin>>ell;
            if(ell == "f")
            {    
                m[i] = new Fire();
            }
            else if(ell == "w")
            {
                m[i] = new Water();
            }
            else if (ell == "e")
            {
                m[i] = new Earth();
            }
            else
            {
                std::cout<<"wrong input\n";
                i--;
            }        
        }    
        Ns[i] = new NatureSpell(m, N);
    }    
    Spell** Sp {new Spell*[2]};
    Sp[0] = new Attack();
    Sp[1] = new Protect();
    Sp[2] = new Unforgivable();
    Wizard wiz = Wizard("Harry", 4, 100, 20, 5, 5); 
    Wizard target = Wizard("Wood", 0, 100, 40);
    std::cout<<"_________________________________________\n";
    Book book = Book("Tom", 19, Ns, N_NS, Sp, 3);
    book.inf(); 
    // Пока что только для Nature sprells
    std::cout<<"What spell do you want to use?(write number)\n";
    int g;
    std::cin>>g;
    try{   
    wiz.use(&book, "NS", g-1, &target);
    //Пример исключения (уровень склишком низкий для использования заклинаний)
    target.use(&book, "NS", g-1, &wiz);
    }
    catch(const int&)
    {
        std::cout<<"Not enough level\n";
    }
    catch(const char*)
    {
        std::cout<<"Too away from you\n";
    }
    target.inf();
    std::cout<<"_____________________________\n";
    Backpack pack = Backpack(new Weapons*[1], 1);
    Orks ork = Orks("Aboba", &pack);
    Ranged bow = Ranged();
    pack.weap[0] = &bow;
    ork.inf();
    ork.use(&wiz, 0);
    wiz.inf();
}