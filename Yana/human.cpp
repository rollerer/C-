#include <iostream>
#include <vector>
#include <memory>
#include "wizard.cpp"
using namespace std;



class Weapon {
protected:
    string name;
    int damage;
    int clip = 0;

public:
    virtual void use(Aang* people) = 0;   
    virtual void inf() const {
        cout << "Weapon: " << name << " Damage: " << damage << "\n";
    }
    virtual ~Weapon() = default;
};

class Knife : public Weapon {
public:
    Knife() { 
        name = "Нож"; 
        damage = 5; 
    }
    void use(Aang* people) override {
        if(!people->resistance){
        people->gain.push_back("Ранен ножом");
        people->health -= damage;
        }
        else{
            people->resistance --;
        }
    }
};

class Grenade : public Weapon {
public:
    Grenade() { 
        name = "Граната"; 
        damage = 100; 
        clip = 1;
    }
    void use(Aang* people) override {
        if(clip!=0){
        if(!people->resistance){
        people->gain.push_back("Взрыв гранаты");
        people->health = 0;
        }
        else{
            people->resistance --;
        }
        clip-=1;
    }  
    }
};

class SubmachineGun : public Weapon {
public:
    SubmachineGun() { 
        name = "Пистолет-пулемет"; 
        damage = 7; 
        clip = 20;
    }
    void use(Aang* people) override {
        if(clip!=0){
        if(!people->resistance){
        people->gain.push_back("Ранен пистолетом-пулеметом");
        people->health -= damage;
        }
        else{
            people->resistance --;
        }
        clip -=1;
    }
    }
};

class Pistol : public Weapon {
public:
    Pistol() { 
        name = "Пистолет"; 
        damage = 10;
        clip = 10; 
    }
    void use(Aang* people) override {
        if(clip!=0){
        if(!people->resistance){
        people->gain.push_back("Ранен пистолетом");
        people->health -= damage;
        }
        else{
            people->resistance --;
        }
        clip -=1 ;
    }
    }
};

class AssaultRifle : public Weapon {
public:
    AssaultRifle() { 
        name = "Автомат"; 
        damage = 12; 
        clip = 40;
    }
    void use(Aang* people) override {
        if(clip!=0){
        if(!people->resistance){
        people->gain.push_back("Ранен автоматом");
        people->health -= damage;
        clip -=1 ;
        }
        else{
            people->resistance --;
        }
    }
    }
};

shared_ptr<Weapon> chooseWeap(string name)
{
    if(name == "Granate")
    {
        return make_shared<Grenade>();
    }
    else if(name == "Pistol")
    {
        return make_shared<Pistol>();
    }
    else if(name == "AssaultRifle")
    {
        return make_shared<AssaultRifle>();
    }
    else if(name == "SubmachineGun")
    {
        return make_shared<SubmachineGun>();
    }
    else
    {
        return make_shared<Knife>();
    }
}

class Inventory {
private:
    vector<shared_ptr<Weapon>> weapons;

public:
    Inventory(string one, string two) {
        weapons.push_back(make_shared<Knife>());
        weapons.push_back(chooseWeap(one));
        weapons.push_back(chooseWeap(two));
    }

    void useWeapons(Aang* people) {
        int selectedCount = 0;

        people->gain.clear();
        for (const auto& weapon : weapons) {
            if (selectedCount < 3) {
                weapon->use(people);
                selectedCount++;
            }
        }
    }

    void inf() {
        for (const auto& weapon : weapons) {
            weapon->inf();
        }
    }
};

class People : public Aang {
    string name;
public: 
    Inventory* inv;
    People* adres = this;
    People(string n, int h, int s, Inventory* i)
    {
        name = n;
        health = h;
        shield = s;
        inv = i;
    }
    void inf() override {
        cout <<name<< ": Здоровье = " << health << ", Щит = " << shield << "\n";
        cout<<"Инвентарь: \n";
        inv->inf();
    }
};