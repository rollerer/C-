#include <iostream>
#include "Target.cpp"
#define water 15
#define water_dist 3
#define fire 30
#define fire_dist 1

// заклинания аля Гарри Поттер[
class Spell
{   protected:
    std::string name;
    int damage;
    int protect;
    int heal;
    public:
    int level;
    virtual void ability(Target*) = 0;
    int dist = 0;
    void inf()
    {
        std::cout<<name;
    }
};
// атакующие заклинания
class Attack: public Spell
{   
    public:
    Attack(int d)
    {
        name = "Attack\n";
        damage = d;
        dist = 4;
    }
    void ability(Target* t)
    {
        t->debuffs[t->FreeDebuff] = "burning\n";
        t->FreeDebuff += 1;
        t->health -= damage;
    }
};
// защитные
class Protect: public Spell
{  
    public:
    Protect(int pr)
    {
        name = "Protect\n";
        protect = pr;
        dist = 3;
    }
    void ability(Target* t)
    {
        t->buffs[t->FreeBuff] = "protected\n";
        t->FreeBuff+=1;
        t->shield+=protect;
    }
};
// бытовые
class Heal: public Spell
{   
    public:
    Heal(int h)
    {
        name = "Heal\n";
        heal = h;
        dist = 3;
    }
    void ability(Target* t)
    {
        t->health+=heal;
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
        int dist = 0;
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
        atack = fire;
        dist = fire_dist;
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
        atack = water;
        dist = water_dist;
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
        atack = 20;
        dist = -1;
    }
};

class NatureSpell
{   
    private:
        Elements** elem;
        int dist = 0;
        
    public:
        int N = 0;
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
            for(int i = 0; i<N; i++)
            {
                dist+=elem[i]->dist;   
            }
            if(dist<0)
            {
                dist = 0;
            }
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

            std::cout<<NAME<<"; level: "<<level<<"\n";
        }
        friend class Wizard;
};

NatureSpell* createNSp(std::string s)
{   
    Elements** m = new Elements*[s.length()];
    std::string ell;
    for(int i = 0; i<s.length(); i++)
    {   
        ell = s[i];
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
    }
    return new NatureSpell(m, s.length());
}

Spell* createHSp(std::string ad)
{   
    std::string n;
    int num = 0;
    n = ad[0];
    if(n == "A")
    {   
        return new Attack(stoi(ad.substr(1)));
    }
    else if(n == "P")
    {
        return new Protect(stoi(ad.substr(1)));
    }
    else if(n == "H")
    {
        return new Heal(stoi(ad.substr(1)));
    }
    else
    {
        return new Unforgivable();
    }
}