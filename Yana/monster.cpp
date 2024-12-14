#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "wizard.cpp"

using namespace std;

class Superpowers {
protected:
    string name;
    int damage = 0;
    int restoring_health = 0;
    int counting_attacks = 3;

public:
    virtual void use(Aang*) = 0;
    virtual void inf() const {
        cout << "Superpowers: " << name << " Damage: " << damage << "\n";
    }
    friend class Monster;
};

class Super_strength: public Superpowers{
    public:
    Super_strength(){
        name = "Super_strength";
        damage = 15;
    }
   void use(Aang* monster) override {
        monster->gain.push_back("Super punch");
        monster->health -= damage; 
   }  
};

class Super_speed: public Superpowers{
    public:
    Super_speed(){
        name = "Super_speed";
        damage = 5;
        restoring_health = 2;
    }
   void use(Aang* monster, Aang* user) {
        monster->gain.push_back("Hook");
        monster->health -= damage;
        user->health += restoring_health; 
   }   
   void use(Aang* a)
   {

   } 
};

class Regeneration: public Superpowers{
    public:
    Regeneration(){
        name = "Regeneration";
        damage = 7;
        counting_attacks = 3;
    }
   void use(Aang* monster, Aang* user) {
        monster->gain.push_back("Two");
        monster->health -= damage;
        if(counting_attacks!=0){
        user->resistance  ++;
        counting_attacks -= 1;
      }
   } 
   void inf(){
        cout<<name<<'\n';
   }
   void use(Aang* a)
   {

   }
};

class Monster: public Aang {
private: 
    string name;
public:
    Superpowers* sup;
    Monster* adres = this;
    Monster(string n, int h, int s, Superpowers* a)
    {   
        health = h;
        name = n;
        shield = s;
        sup = a;
    }
    void inf()
    {   
        cout << "Монстр: " << name <<"\n"<< "Здоровье: " << health << "\n"<<"Щит: " << shield << "\n";
        sup->inf();
    }
};

Superpowers* createSup(string sup)
{
    if(sup == "Regeneration")
    {
        return new Regeneration();
    }
    else if(sup == "Speed")
    {
        return new Super_speed();
    }
    else
    {
        return new Super_strength();
    }
}