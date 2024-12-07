#include <iostream>
#include "Spells.cpp"

class Book
{   
    public:
    int pages;
    std::string name;
    Spell** Harry_spells;
    NatureSpell** Nature_spells;
    int Nat_Sp;
    int Har_Sp;
    Book(std::string n, int p, NatureSpell** ns, int n_ns)
    {
        name = n;
        pages = p;
        Nature_spells = ns;
        Nat_Sp = n_ns;
        Har_Sp = 0;
        Harry_spells = new Spell*[0];
    }
    Book()
    {
        pages = 0;
        name = "";
        Harry_spells = new Spell*[0];
        Nature_spells = new NatureSpell*[0];
        Nat_Sp = 0;
        Har_Sp = 0;
    }
    Book(std::string n, int p, NatureSpell** ns, int n_ns, Spell** sp, int s)
    {
        name = n;
        pages = p;
        Nature_spells = ns;
        Nat_Sp = n_ns;
        Harry_spells = sp;
        Har_Sp = s;
    }
    Book(std::string n, int p)
    {
        name = n;
        pages = p;
        Nature_spells = new NatureSpell*[0];
        Nat_Sp = 0;
        Harry_spells = new Spell*[0];
        Har_Sp = 0;
    }
    void inf()
    {
        std::cout<<"Name: "<<name<<"\n";
        std::cout<<"Nature spells: \n";
        for(int i = 0; i<Nat_Sp; i++)
        {   
            Nature_spells[i]->inf();
        }
        std::cout<<"Harry Potter spells: \n";
        for(int i = 0; i<Har_Sp; i++)
        {
            Harry_spells[i]->inf();
        }

    }

    
};


class Wizard: public Target
{   
    public:
    std::string name;
    int level;  
    Book* book;
    Wizard(std::string n, int l, int h, int p)
    {
        name = n;
        level = l;
        health = h;
        shield = p;
    }
    Wizard(std::string n, int l, int h, int p, int x, int y, Book* b)
    {
        name = n;
        level = l;
        health = h;
        shield = p;
        coord[0] = x;
        coord[1] = y;
        book = b;
    }
    void inf()
    {       
            std::cout<<"Name: "<<name<<'\n';
            std::cout<<"health: "<<health<<'\n';
            std::cout<<"shield: "<<shield<<'\n';
            std::cout<<"Debuffs: \n";
            for (int i = 0; i<FreeDebuff; i++)
            {
                std::cout<<debuffs[i];
            }
            std::cout<<"Buffs: \n";
            for (int i = 0; i<FreeBuff; i++)
            {
                std::cout<<buffs[i];
            }
            std::cout<<"Book: "<<'\n';
            book->inf();
            std::cout<<"______________________________________\n";

    }
    void use(std::string n, int num, Target* t)
    {   
        if(n == "Ns")
        {
        NatureSpell* sp = book->Nature_spells[num];
        for(int i = 0; i<4; i++)
        {
            if(dist(this, t) <= sp->dist)
            {
                if(sp->level <= level)
                {
                    sp->effect(t);
                    break;
                }
                else
                {
                    throw(1);
                }
            }
            else
            {   
                move(this, t);
            }
        }
        }
        else
        {
            Spell* hsp = book->Harry_spells[num];
            for(int i = 0; i<4; i++)
            {
                if(dist(this, t) <= hsp->dist)
                {
                    if(hsp->level <= level)
                    {
                        hsp->ability(t);
                        break;
                    }
                    else
                    {
                        throw(1);
                    }
                }
                else
                {   
                    move(this, t);
                }
            }
        }
    }
};