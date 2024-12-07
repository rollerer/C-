#include <iostream>
#include <fstream>
#include <sstream>
#include "Magic.cpp"
#include "Orks.cpp"

int duel(Wizard* a, Orks* b, int i)
{   
    if(b->health > 0 and a->health > 0)
    {
        a->use("Ns", i, b);
        if(b->health <= 0)
        {   
            a->level++;
            std::cout<<b->name<<" is dead\n";
            return 1;
        }
    }
    return 0;
}
int duel(Orks* b, Wizard* a, int i)
{
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
void show(Wizard**a, Orks**b, int wiz, int ork)
{   
    int flag = 0;
    std::cout<<"_______________________________________________________\n";
    for(int i = 0; i<15; i++)
    {
        for(int j = 0; j<15; j++)
        {   
            flag = 0;
            for(int k = 0; k<wiz; k++)
            {
                if(a[k]->coord[0]==j and a[k]->coord[1] == i)
                {   
                    if(!flag)
                    {
                        std::cout<<"m";
                        flag = 1;
                    }
                }
            }
            if(!flag)
            {
            for(int k = 0; k<ork; k++)
            {
                if(b[k]->coord[0]==j and b[k]->coord[1] == i)
                {   
                    if(!flag)
                    {
                        std::cout<<"o";
                        flag = 2;
                    }
                }
            }
            }
            if(!flag)
            {
                std::cout<<" ";
            }
        }
        std::cout<<'\n';
    }
    std::cout<<"_______________________________________________________\n";
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
    int x_wiz = 0;

    Orks** Orki = new Orks*[0];
    std::string name_ork = "";
    std::string name_backpack = "";
    int num_weap = 0;
    int ork = 0;
    int dead_ork = 0;
    int x_ork = 0;

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
            Wizards[wiz] = new Wizard(name_wiz, 1, 100, 20, x_wiz*2, 0, new Book(name_book, 19));
            x_wiz++;
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

            Orki[ork] = new Orks(name_ork, 1, 100, 20, x_ork*2, 10, new Backpack(new Weapons*[0], 0));
            x_ork++;
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
    int tar_w = 0;
    int tar_o = 0;
    Wizard* target_wiz = Wizards[tar_w];
    Orks* target_ork = Orki[tar_o];
    while(wiz!=dead_wiz and ork!=dead_ork)
    {   
        target_wiz = Wizards[tar_w];
        for(int i = 0; i<wiz; i++)
        {
            try
            {   
                n = duel(Wizards[i], Orki[tar_o], Wizards[i]->level-1);
                if(n == 1)
                {
                    dead_ork++;
                    tar_o ++;
                    break;
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
        for(int i = 0; i<ork; i++)
        {
            try
            {   
                n = duel(Orki[i], target_wiz, 0);
                if(n == 1)
                {
                    dead_wiz++;
                    tar_w++;
                    break;
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
        show(Wizards, Orki, wiz, ork);
    }
    if(wiz == dead_wiz)
    {
        std::cout<<"Orks Win!\n";
    }
    else
    {
        std::cout<<"Wizards Win!\n";
    }
}