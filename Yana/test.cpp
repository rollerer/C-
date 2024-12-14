#include "human.cpp"
#include "monster.cpp"
#include <fstream>
#include <sstream>
using namespace std;

string triel(People* human, Wizard* wiz, Monster* monst, Book* book)
{   
    bool flag = 0;
    while(flag == 0)
    {   
        if(human->health>0)
        {
            human->inv->useWeapons(wiz);
            if(wiz->health<=0)
            {
                flag = 1;
                return "w";
            }
        }
        if(monst->health>0)
        {    
            monst->sup->use(human);
            if(human->health<=0)
            {
                flag = 1;
                return "h";
            }
        }
        if(wiz->health>0)
        {
            wiz->use(monst, "Ns", book);
            if(wiz->health<=0)
            {
                flag = 1;
                return "m";
            }
        }
    }
}

main() {
    string type;
    ifstream file("War.txt");
    string s;
    string d;

    string name_wiz = "";
    int dead_wiz = 0;
    int health;
    int shield;

    string name_mon = "";
    int dead_mon = 0;
    string super;

    string name_hum = "";
    int dead_hum = 0;
    string first_weap;
    string second_weap;

    vector<shared_ptr<NatureSpell>> NS;
    vector<shared_ptr<Spell>> S;
    vector<shared_ptr<Monster>> Monst;
    vector<shared_ptr<Wizard>> Wiz;
    vector<shared_ptr<People>> Hum;
    Book book = Book("Book");



    while(getline(file, s))
    {   
        if(s == "Monsters")
        {
            type = "mon";
            getline(file,s);
        }
        else if(s == "Wizards")
        {
            type = "wiz";
            getline(file,s);
        }
        else if(s == "People")
        {
            type = "hum";
            getline(file,s);
        }
        else if(s == "Book")
        {
            type = "book";
            getline(file,s);
        }
        if(type == "wiz")
        {
            stringstream str(s);
            str>>name_wiz;
            str>>health;
            str>>shield;
            Wiz.push_back(make_shared<Wizard>(name_wiz, health, shield));
        }
        if(type == "hum")
        {
            stringstream str(s);
            str>>name_hum;
            str>>health;
            str>>shield;
            str>>first_weap;
            str>>second_weap;
            Hum.push_back(make_shared<People>(name_hum, health, shield, new Inventory(first_weap, second_weap)));            
        }
        if(type == "mon")
        {
            stringstream str(s);
            str>>name_mon;
            str>>health;
            str>>shield;
            str>>super;
            Monst.push_back(make_shared<Monster>(name_mon, health, shield, createSup(super)));
        }
        if(type == "book")
        {
            stringstream str(s);
            string fl = "";
            while(str>>d)
            {   
                if(d == "NatureSpells")
                {
                    fl = "Ns";
                    str>>d;
                }
                else if(d == "HarrySpells")
                {
                    fl = "Hs";
                    str>>d;
                }
                if(fl == "Ns")
                {
                book.addNatureSpell(createNSp(d));
                }
                else if(fl == "Hs")
                {
                    book.addSpell(createHSp(d));
                }
            }
        }
    }

    book.inf();
    cout << "Перед боем:\n";

    for(const auto& wiz : Wiz)
    {
        cout<<'\n';
        wiz->inf();
    }
    for(const auto& mon : Monst)
    {
        cout<<'\n';
        mon->inf();
    }
    for(const auto& hum : Hum)
    {
        cout<<'\n';
        hum->inf();
    }
    string t;
    while((Hum.back()->health>0 and Wiz.back()->health>0) or (Wiz.back()->health>0 and Monst.back()->health>0) or (Monst.back()->health>0 and Hum.back()->health>0))
    {   
        try{
            std::cout<<"Human: "<<Hum.size()<< "\nWizard: "<< Wiz.size()<<"\nMonsters: "<<Monst.size()<<'\n';
            t = triel(Hum.back()->adres, Wiz.back()->adres, Monst.back()->adres, &book);
            if(t == "w")
            {   
                if(Wiz.size() != 1)
                {
                    Wiz.pop_back();
                }
            }
            else if(t == "h")
            {   
                if(Hum.size() != 1)
                {
                    Hum.pop_back();
                }
            }
            else if(t == "m")
            {   
                if(Monst.size() != 1)
                {
                    Monst.pop_back();
                }
            }
        }
        catch(...)
        {
            cout << "Жаль этого добряка...\n";
        }
    }
    if(Hum.back()->health>0)
    {
        cout<<"People Win!";
    }
    else if(Wiz.back()->health>0)
    {
        cout<<"Wizards Win!";
    }
    else if(Monst.back()->health>0)
    {
        cout<<"Monsters Win!";
    }
}
