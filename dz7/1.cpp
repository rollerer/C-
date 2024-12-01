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
        std::string* debuffs {new std::string[20]};
        std::string* buffs {new std::string[20]};
        int size;
        int FreeDebuff = 0;
        int FreeBuff = 0;
        virtual void inf() = 0;
        
};

// заклинания аля Гарри Поттер[
class Spell
{   protected:
    int damage;
    int protect;
    int heal;
    int level;
    virtual void ability(Target*) = 0;
};
// атакующие заклинания
class Attack: public Spell
{
    void ability(Target* t)
    {
        t->debuffs[t->FreeDebuff] = "burning";
        t->FreeDebuff += 1;
        t->health -= 18;
    }
};
// защитные
class Protect: public Spell
{  
    void ability(Target* t)
    {
        t->buffs[t->FreeBuff] = "protected";
        t->FreeBuff+=1;
    }
};
// бытовые
class Household: public Spell
{   
    void ability(Target* t)
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
        int atack = 0;
        int protect = 0;
        std::string name;
    public:
        virtual void effect(Target* , int) = 0;
        friend class NatureSpell;
};

//элемент огня
class Fire: public Elements
{   
    public:
    void effect(Target* t, int i)
    {
        t->debuffs[t->FreeDebuff] = "burning\n";
        t->FreeDebuff+=1;
    }
    Fire()
    {   
        atack = 10;
        name = "fi";
    }
};

//элемент воды
class Water: public Elements
{   
    public:
    void effect(Target* t, int i)
    {
        t->debuffs[t->FreeDebuff] = "wash\n";
        t->FreeDebuff+=1;
    }
    Water()
    {
        name = "wa";
        atack = 5;
    }
};

// элемент земли
class Earth: public Elements
{
    public:
    void effect(Target* t, int i)
    {   
        t->buffs[t->FreeBuff] = "stone\n";
        t->FreeBuff+=1;
    }
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
            int ttt = 0;
            for(int i = 0; i<N; i++)
            {   
                elem[i]->effect(t, i);
                total_damage = SUM(total_damage, elem[i]->atack);
                total_shield = SUM(total_shield, elem[i]->protect);
            }

            if(total_damage>t->shield)
            {   
                total_damage-=t->shield;
                t->shield = 0;
                t->health -= total_damage;
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
class Wizard: public Target
{   
    public:
    std::string name;
    int level;  
    Wizard(std::string n, int l, int h, int p)
    {
        name = n;
        level = l;
        health = h;
        shield = p;
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
    }
    void use(Book* book, std::string n, int num, Target* t)
    {   
        if(book->Nature_spells[num]->level <= level)
        {
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
    Wizard wiz = Wizard("Harry", 4, 100, 20); 
    Wizard target = Wizard("Harry", 5, 100, 40);
    std::cout<<"_________________________________________\n";
    Book book = Book("Tom", 19, Ns, N_NS);
    book.inf(); 
    std::cout<<"What spell do you want to use?(write number)\n";
    int g;
    std::cin>>g;
    try{   
    wiz.use(&book, "NS", g-1, &target);
    }
    catch(const int&)
    {
        std::cout<<"Not enough level\n";
    }
    target.inf();
}