#include <iostream>
#include <fstream>
#include <sstream>
#include "Magic.cpp"
#include "Orks.cpp"

int duel(Wizard* a, Orks* b, int i)
{   
    if(b->health > 0 and a->health > 0)
    {
        a->use("Hs", i, b);
        if(b->health <= 0)
        {   
            a->level++;
            std::cout<<b->name<<" is dead\n";
            return 2;
        }
    }
    if(b->health > 0 and a->health > 0)
    {
        b->use(a, i);
        if(a->health <= 0)
        {   
            b->skill ++;
            std::cout<<a->name<<" is dead\n";
            return 1;
        }
    }
    return 0;
} 

main()
{   
    std::string type;
    std::ifstream file("file.txt");
    std::string s;
    std::string d;
    
    Wizard** Wizards = new Wizard*[0];
    std::string name_wiz = "";
    std::string name_book = "";
    int num_sp = 0;
    int num_har = 0;
    int wiz = 0;
    int dead_wiz = 0;

    Orks** Orki = new Orks*[0];
    std::string name_ork = "";
    std::string name_backpack = "";
    int num_weap = 0;
    int ork = 0;
    int dead_ork = 0;

    while(std::getline(file, s))
    {   
        if(s == "Spells")
        {   
            type = "sp";
            std::getline(file,s);
        }
        else if(s == "Orks")
        {
            type = "ork";
            std::getline(file,s);
        }
        else if(s == "Wizards")
        {
            type = "wiz";
            std::getline(file,s);
        }
        if(type == "sp")
        {
            std::stringstream str(s);
            str>>name_wiz;
            name_book = name_wiz + "'s book";
            Wizards[wiz] = new Wizard(name_wiz, 1, 100, 20, 0, 0, new Book(name_book, 19));
            std::string fl = "";
            while(str>>d)
            {   
                if(d == "NatureSpells")
                {
                    fl = "Ns";
                    str>>d;
                }
                else if(d == "HarrySpells")
                {
                    fl = "Hs";
                    str>>d;
                }
                if(fl == "Ns")
                {
                Wizards[wiz]->book->Nature_spells[num_sp] = createNSp(d);
                Wizards[wiz]->book->Nat_Sp++;
                num_sp++;
                }
                else if(fl == "Hs")
                {
                    Wizards[wiz]->book->Harry_spells[num_har] = createHSp(d);
                    Wizards[wiz]->book->Har_Sp++;
                    num_har ++;
                }
            }
            wiz ++;
            num_sp = 0;
        }
        if(type == "ork")
        {
            std::stringstream str(s);
            str>>name_ork;
            name_backpack = name_ork + "'s backpack";
            Orki[ork] = new Orks(name_ork, 1, 100, 20, 0, 10, new Backpack(new Weapons*[0], 0));
            while(str>>d)
            {
                Orki[ork]->pack->weap[num_weap] = createWeap(d);
                Orki[ork]->pack->Weap ++;
                num_weap++;

            }
            ork ++;
            num_weap = 0;
        }
        s = "";
    }
    int n;
    for(int i = 0; i< 20; i++)
    {
        try
        {   
            n = duel(Wizards[0], Orki[0], 0);
            if(n == 2)
            {
                dead_ork++;
            }  
            else if(n == 1)
            {
                dead_wiz ++;
            }
        }
        catch(const char*)
        {
            std::cout<<"Can't reach\n";
        }
        catch (const int&)
        {
            std::cout<<"Not enough\n";
        }        
        
    }
    Orki[0]->inf();
}