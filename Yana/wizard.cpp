#include <iostream>
#include <vector>
#include <memory>
#ifndef M
#define M
using namespace std;

template <typename T>
T SUM(const T& a, const T& b) {
    return a + b;
}

class Aang {
public:
    int health;
    int shield;
    vector<string> blinding;
    vector<string> gain;
    int resistance = 0;

    virtual void inf() = 0; 
};

class Spell {
protected:
    string name;

public:
    virtual void apply(Aang* aang) = 0; 
    virtual void inf() const {
        cout << "spell: " << name << "\n";
    }
    virtual ~Spell() = default;
};

class Attack : public Spell {
public:
    Attack() { name = "Attack"; }
    void apply(Aang* aang) {
        if(!aang->resistance)
        {
        aang->blinding.push_back("Burning");
        aang->health -= 17;
        }
        else{
            aang->resistance --;
        }
    }
};

class Protect : public Spell {
public:
    Protect() { name = "Protect"; }
    void apply(Aang* aang)  {
        aang->gain.push_back("Shielded");
    }
};

class Household : public Spell {
public:
    Household() { name = "Household"; }
    void apply(Aang* aang) {
        cout << "Бытовое заклинание не предназначено для боя.\n";
    }
};

class Unforgivable : public Spell {
public:
    Unforgivable() { name = "Unforgivable"; }
    void apply(Aang* aang) {
        cout << "Не стоит использовать это заклинание.\n";
    }
};

/*class Heal : public Spell {
private:
    int healAmount;

public:
    Heal(int amount) : healAmount(amount) {
        name = "Heal";
    }

    void apply(Aang* aang) {
        aang->health += healAmount; 
        cout << "Цель восстановила " << healAmount << " здоровья.\n";
    }

    void inf() const override {
        cout << "Заклинание: " << name << " (восстанавливает " << healAmount << " здоровья)\n";
    }
};*/

class Element {
protected:
    string name;
    int attack = 0;
    int protection = 0;

public:
    virtual void effect(Aang* aang) = 0;
    friend class NatureSpell;
};

class Fire : public Element {
public:
    Fire() { name = "Fire"; attack = 11; }
    void effect(Aang* aang) {
        if(!aang->resistance)
        {
        aang->blinding.push_back("Burning");
        }
        else{
            aang->resistance--;
        }
    }
};

class Water : public Element {
public:
    Water() { name = "Water"; attack = 7; }
    void effect(Aang* aang)  {
        if(!aang->resistance){
        aang->blinding.push_back("Drenched");
        }
        else{
            aang->resistance --;
        }
    }
};

class Earth : public Element {
public:
    Earth() { name = "Earth"; protection = 3; }
    void effect(Aang* aang)  {
        aang->gain.push_back("Stoned"); 
    }
};

class Air : public Element {
public:
    Air() { name = "Air"; protection = 9; } 
    void effect(Aang* aang)  {
        aang->gain.push_back("Air barrier"); 
    }
};

class NatureSpell {
private:
    vector<shared_ptr<Element>> elements;

public:
    NatureSpell(const vector<shared_ptr<Element>>& elems) : elements(elems) {}

    void apply(Aang* aang) {
        int total_damage = 0, total_protection = 0;

        for (const auto& elem : elements) {
            elem->effect(aang);
            total_damage = SUM(total_damage,elem->attack);
            total_protection = SUM(total_protection, elem->protection);
        }
        if (aang->health <= 0) {
            throw("Barbie");
        }
        if (total_damage > aang->shield) {
            total_damage -= aang->shield;
            aang->shield = 0;
            aang->health -= total_damage;
        } else {
            aang->shield -= total_damage;
        }
        aang->shield += total_protection; 
    }

    void inf() {
        cout << "Nature Spell: ";
        for (const auto& elem : elements) {
            cout << elem->name << " ";
        }
        cout << "\n";
    }
};

class Book {
private:
    string name;
    vector<shared_ptr<Spell>> spells;
    vector<shared_ptr<NatureSpell>> natureSpells;

public:
    Book(const string& n) : name(n) {}

    void addSpell(const shared_ptr<Spell>& spell) {
        spells.push_back(spell);
    }

    void addNatureSpell(const shared_ptr<NatureSpell>& spell) {
        natureSpells.push_back(spell);
    }

    void inf() const {
        cout << "Книга: " << name << "\n"<<"Заклинания:\n";
        for (const auto& spell : spells) {
            spell->inf();
        }
        for (const auto& nSpell : natureSpells) {
            nSpell->inf();
        }
    }

    void use(Aang* a, string type)
    {
        if(type == "Ns")
        {
        for(const auto& nassp: natureSpells)
        {
            nassp->apply(a);
        }
        }
        else
        {
        for(const auto& sp: spells)
        {
            sp->apply(a);
        }
        }

    }
};

class Wizard : public Aang {
private:
    string name;

public:
    Wizard* adres = this;
    Wizard(const string& n, int h, int s) : name(n) {
        health = h;
        shield = s;
    }

    void inf() override {
        cout << "Маг: " << name <<"\n"<< "Здоровье: " << health << "\n"<<"Щит: " << shield << "\n";
        cout << "Плюшки: ";
        for (const auto& buff : gain) {
            cout << buff << " ";
        }
        cout << "********: ";
        for (const auto& debuff : blinding) {
            cout << debuff  << " ";
        }
        cout << "\n";
    }
    void use(Aang* a, string i, Book* book)
    {
        book->use(a, i);
    }
};
shared_ptr<NatureSpell> createNSp(std::string s)
{   
    vector<shared_ptr<Element>> elem;
    std::string ell;
    for(int i = 0; i<s.length(); i++)
    {   
        ell = s[i];
        if(ell == "f")
        {    
            elem.push_back(make_shared<Fire>());
        }
        else if(ell == "w")
        {
            elem.push_back(make_shared<Water>());
        }
        else if (ell == "e")
        {
            elem.push_back(make_shared<Earth>());
        }       
        else
        {
            elem.push_back(make_shared<Air>());
        }
    }
    return make_shared<NatureSpell>(elem);
}

shared_ptr<Spell> createHSp(std::string ad)
{   
    std::string n;
    int num = 0;
    n = ad[0];
    if(n == "A")
    {   
        return make_shared<Attack>();
    }
    else if(n == "P")
    {
        return make_shared<Protect>();
    }
    else
    {
        return make_shared<Unforgivable>();
    }
}
#endif