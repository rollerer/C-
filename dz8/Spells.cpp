#include <iostream>
#include "Target.cpp"

// заклинания аля Гарри Поттер[
class Spell
{   protected:
    std::string name;
    int damage;
    int protect;
    int heal;
    int level;
    virtual void ability(Target*) = 0;
    public:
    void inf()
    {
        std::cout<<name;
    }
};
// атакующие заклинания
class Attack: public Spell
{   
    public:
    Attack()
    {
        name = "Attack\n";
    }
    void ability(Target* t)
    {
        t->debuffs[t->FreeDebuff] = "burning\n";
        t->FreeDebuff += 1;
        t->health -= 18;
    }
};
// защитные
class Protect: public Spell
{  
    public:
    Protect()
    {
        name = "Protect\n";
    }
    void ability(Target* t)
    {
        t->buffs[t->FreeBuff] = "protected\n";
        t->FreeBuff+=1;
    }
};
// бытовые
class Household: public Spell
{   
    public:
    Household()
    {
        name = "Household\n";
    }
    void ability(Target* t)
    {
        std::cout<<"it is not a fight spell\n";
    }
};
// непростительные
class Unforgivable: public Spell
{   
    public:
    Unforgivable()
    {
        name = "Unforgivable\n";
    }
    std::string curse;
    void ability(Target* t)
    {
        std::cout<<"better dont use it\n";
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
        int dist = 0;
        
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
            dist = N + 1;
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
        friend class Wizard;
};