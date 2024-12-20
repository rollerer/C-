#include <iostream>
#include "Target.cpp"

class Weapons
{
    protected:
    int damage;
    int range;
    float delay;
    int skill = 0;
    std::string type;
    virtual void ability(Target*, int) = 0;
    void inf()
    {
        std::cout<<"Type: "<<type<<"\n";
    }
    friend class Backpack;
    friend class Orks;
};

class Melee: public Weapons
{
    public:
    Melee(std::string t)
    {   

        if(t == "sword")
        {
            range = 5;
            damage = 15;
            delay = 2;
            skill = 1;
            type = "Sword";
        }
        else if(t == "dagger")
        {
            range = 1;
            damage = 10;
            delay = 0.5;
            skill = 1;
            type = "Dagger";
        }
        else
        {
            throw(1);
        }
    }   
    void ability(Target* t, int s)
    {
        damage = damage*(s+1)/2;
        if(t->shield>damage)
        {
            t->shield-=damage;
        }
        else if(t->shield > 0)
        {
            t->health -= (damage - t->shield);
        }
        else
        {
        t->health-=damage;
        }
    }
};



class Ranged: public Weapons
{   
    public:
    Ranged()
    {
        damage = 40;
        range = 10;
        delay = 5;
        type = "Bow";
    }
    void ability(Target* t, int s)
    {   
        damage = damage*(s+1)/2;
        if(t->shield>damage)
        {
            t->shield-=damage;
        }
        else if(t->shield > 0)
        {
            t->health -= (damage - t->shield);
        }
        else
        {
        t->health-=damage;
        }
    }
};

class TreeStaff: public Weapons
{   
    int heal;
    public:
    TreeStaff()
    {
        heal = 30;
        range = 8;
        delay = 10;
    }
    void ability(Target* t, int s)
    {
        t->health += heal*(s+1)/2;
    }
};


class Backpack
{
    std::string owner = "Unsigned";
    void inf()
    {
        std::cout<<"Owner: "<<owner<<'\n';
        for(int i = 0; i<Weap; i++)
        {
            weap[i]->inf();
        }
    }
    public:
    int Weap = 0;
    Weapons** weap;
    Backpack(Weapons** w, int W)
    {
        weap = w;
        Weap = W;
    }
    friend class Orks;
};

class Orks: public Target
{   
    public:
    std::string name;
    Backpack* pack;
    std::string type;
    int skill;
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
        pack->inf();
        std::cout<<"___________________________________\n";
    }
    Orks(std::string n, std::string t, int s, int h, int pr, int x, int y, Backpack* p)
    {
        name = n;
        pack = p;
        pack->owner = name;
        skill = s;
        health = h;
        shield = pr;
        type = t;
        coord[0] = x;
        coord[1] = y;
    }
    void use(Target* t, int i)
    {
        Weapons* weap = pack->weap[i];
        for(int k = 0; k<6; k++)
        {
            if(dist(this, t) <= weap->range)
            {
                if(weap->skill <= skill)
                {
                    weap->ability(t, skill);
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
                throw("");
            }
        }
    }
    friend class Backpack;
};

Weapons* createWeap(std::string a)
{
    if(a == "sword")
    {
        return new Melee(a);
    }
    else if(a == "dagger")
    {
        return new Melee(a);
    }
    else if(a == "bow")
    {
        return new Ranged();
    }
    else
    {
        return new TreeStaff();
    }

}

Orks* findWeakestOrk(Orks** a, int ork)
{   
    int hp = a[0]->health;
    Orks* ptr = a[0];
    for(int i = 0; i < ork; i++)
    {
        if(a[i]->health < hp)
        {
            hp = a[i]->health;
            ptr = a[i];
        }
    }
    return ptr;
}
