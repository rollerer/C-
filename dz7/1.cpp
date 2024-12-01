#include <iostream>

template <typename T> T SUM(T& a, T& b)
{
    T s = a + b;
    return s;
}
template <typename T> int SIZE(T& a)
{
    int size = sizeof(a)/sizeof(*a);
    return size;
}

class Target
{   
    public:
        int health;
        int shield;
        std::string* debuffs;
        std::string* buffs;
        int size;
        Target(int h, int s, std::string* d, std::string* b, int n)
        {
            health = h;
            shield = s;
            debuffs = d;
            buffs = b;
            size = n;

        }
        void inf()
        {
            std::cout<<"health: "<<health<<'\n';
            std::cout<<"shield: "<<shield<<'\n';
            std::cout<<"Debuffs: \n";
            for (int i = 0; i<size; i++)
            {
                std::cout<<debuffs[i];
            }
            std::cout<<"Buffs: \n";
            for (int i = 0; i<size; i++)
            {
                std::cout<<buffs[i];
            }
        }
};

// заклинания аля Гарри Поттер[
class Spell
{   protected:
    int damage;
    int protect;
    int heal;
    int level;
    virtual void ability() = 0;
};
// атакующие заклинания
class Attack: public Spell
{
    void ability()
    {
        
    }
};
// защитные
class Protect: public Spell
{  
    void ability()
    {
        
    }
};
// бытовые
class Household: public Spell
{   
    void ability()
    {
        
    }
};
// непростительные
class Unforgivable: public Spell
{   
    std::string curse;
    void ability()
    {

    }
};




// ]


// стихийные заклинания [
class Elements
{   protected:
        int atack;
        int protect;
        std::string name;
    public:
        virtual void effect(Target* , int) = 0;
        friend class NatureSpell;
};

//элеиент огня
class Fire: public Elements
{   
    
    void effect(Target* t, int i)
    {
        t->debuffs[i] = "burning\n";
    }
    public:
    Fire()
    {   
        atack = 10;
        name = "fi";
    }
};

//элемент воды
class Water: public Elements
{   
    void effect(Target* t, int i)
    {
        t->debuffs[i] = "wash\n";
    }
    public:
    Water()
    {
        name = "wa";
        atack = 5;
    }
};

// элемент земли
class Earth: public Elements
{
    
    void effect(Target* t, int i)
    {   
        t->buffs[i] = "stone\n";
    }
    public:
    Earth()
    {
        name = "ear";
        protect = 8;
    }
};



class NatureSpell
{   
    private:
        Elements** elem;
        
        
    public:
        int N;
        int level;
        void effect(Target* t)
        {   
            int total_damage = 0;
            int total_shield = 0;
            int ttt;
            for(int i = 0; i<N; i++)
            {   
                elem[i]->effect(t, i);
                total_damage = SUM(total_damage, elem[i]->atack);
                total_damage = SUM(total_damage, elem[i]->protect);
            }

            if(total_damage>t->shield)
            {   
                ttt = -t->shield;
                total_damage = SUM(total_damage, ttt);
                t->shield = 0;
                ttt = - total_damage;
                t->health = SUM(t->health, ttt);
            }
            else
            {  
                t->shield-=total_damage;
            }
            t->shield+=total_shield;
        }
        NatureSpell(Elements** el, int n)
        {
            elem = el;
            N = n;
            level = int(N/3)+1;
        }
        NatureSpell()
        {
            elem = 0;
            N = 0;
        }
        void inf()
        {   
            std::string NAME = "";
            for(int i = 0; i < N; i++)
            {   
                NAME = SUM(NAME, elem[i]->name);
            }

            std::cout<<"name of spell: "<<NAME<<"; level: "<<level<<"\n";
        }
};

class Book
{   
    public:
    int pages;
    std::string name;
    Spell** Harry_spells;
    NatureSpell** Nature_spells;
    int Nat_Sp;    
    Book(std::string n, int p, NatureSpell** ns, int n_ns)
    {
        name = n;
        pages = p;
        Nature_spells = ns;
        Nat_Sp = n_ns;
    }
    Book(std::string n, int p, NatureSpell** ns)
    {
        name = n;
        pages = p;
        Nature_spells = ns;
    }
    void inf()
    {
        std::cout<<"Name: "<<name<<"\n";
        std::cout<<"Nature spells: \n";
        for(int i = 0; i<Nat_Sp; i++)
        {   
            Nature_spells[i]->inf();
        }

    }

};
class Wizard
{   
    public:
    std::string name;
    int level;  
    Wizard(std::string n, int l)
    {
        name = n;
        level = l;
    }
    void use(Book* book, std::string n, int num, Target* t)
    {   
        if(book->Nature_spells[num]->level <= level)
        {
            std::cout<<book->Nature_spells[num]->N<<'\n';
        book->Nature_spells[num]->effect(t);
        }
        else
        {
            throw(1);
        }
    }
};
// ]


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
        Fire f = Fire();
        Water w = Water();
        Earth e = Earth();
        std::string ell;
        for(int i = 0; i<N; i ++)
        {   
            std::cout<<"Write "<<N<<" elements: fire (f), water (w), earth (e)\n";
            std::cin>>ell;
            if(ell == "f")
            {   
                f = Fire(); 
                m[i] = &f;
            }
            else if(ell == "w")
            {
                w = Water();
                m[i] = &w;
            }
            else if (ell == "e")
            {
                e = Earth();
                m[i] = &e;
            }
            else
            {
                std::cout<<"wrong input\n";
                i--;
            }        
        }    
        Ns[i] = new NatureSpell(m, N);
    }    
    std::string *b {new std::string[N]};
    std::string *d {new std::string[N]};
    Wizard wiz = Wizard("Harry", 4); 
    Target target = Target(100, 19, d, b, N);
    std::cout<<"_________________________________________\n";
    Book book = Book("Tom", 19, Ns, N_NS);
    book.inf(); 
    std::cout<<"What spell do you want to use?(write number)\n";
    int g;
    std::cin>>g;
    try{   
    wiz.use(&book, "NS", g-1, &target);
    }
    catch(...)
    {
        std::cout<<"Not enough level\n";
    }
}