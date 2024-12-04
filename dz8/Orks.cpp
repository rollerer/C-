#include <iostream>
#include "Target.cpp"

class Weapons
{
    protected:
    int damage;
    int range;
    float delay;
    int skill;
    std::string type;
    virtual void ability(Target*) = 0;
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
    Melee(std::string type)
    {
        if(type == "sword")
        {
            range = 2;
            damage = 5;
            delay = 2;
            skill = 2;
            type = "Sword";
        }
        else if(type == "dagger")
        {
            range = 1;
            damage = 3;
            delay = 0.5;
            skill = 1;
            type = "Dagger";
        }
        else
        {
            throw(1);
        }
    }   
    void ability(Target* t)
    {
        t->health -= damage;
    }
};



class Ranged: public Weapons
{   
    public:
    Ranged()
    {
        damage = 10;
        range = 10;
        delay = 5;
        type = "Bow";
    }
    void ability(Target* t)
    {
        t->health-=damage;
    }
};

class TreeStaff: public Weapons
{   
    int heal;
    public:
    TreeStaff()
    {
        heal = 10;
        range = 8;
        delay = 10;
    }
    void ability(Target* t)
    {
        t->health+= heal;
    }
};


class Backpack
{
    std::string owner = "Unsigned";
    int Weap = 0;
    void inf()
    {
        std::cout<<"Owner: "<<owner<<'\n';
        for(int i = 0; i<Weap; i++)
        {
            weap[i]->inf();
        }
    }
    public:
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
    std::string name;
    Backpack* pack;
    public:
    int skill;
    void inf()
    {
        std::cout<<"Name: "<<name<<"\n";
        pack->inf();
    }
    Orks(std::string n, Backpack* p)
    {
        name = n;
        pack = p;
        pack->owner = name;
    }
    void use(Target* t, int i)
    {
        Weapons* weap = pack->weap[i];
        for(int k = 0; k<4; k++)
        {
            if(dist(this, t) < weap->range)
            {
                if(weap->skill <= skill)
                {
                    weap->ability(t);
                }
                else
                {
                    throw(1);
                }
            }
            else
            {   
                move(this, t);
                std::cout<<dist(this, t)<<'\n';
                throw("");
            }
        }
    }
    friend class Backpack;
};
