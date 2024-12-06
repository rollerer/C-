#include <iostream>
#include <fstream>
#include <sstream>
#include "Magic.cpp"
#include "Orks.cpp"
void duel(Wizard* a, Orks* b, int i)
{
    a->use("Ns", i, b);
    b->use(a, i);
} 

main()
{   
    std::string s;
    std::string d;
    Wizard** Wizards = new Wizard*[0];
    std::string type;
    std::ifstream file("file.txt");
    Book* book{new Book()};
    NatureSpell** m{new NatureSpell*[0]};
    std::string name_wiz = "";
    std::string name_book = "";
    int num_sp = 0;
    int wiz = 0;
    while(std::getline(file, s))
    {   
        if(s == "Spells")
        {   
            type = "sp";
            std::getline(file,s);
        }
        else if(s == "Orks")
        {
            type = "ork";
            std::getline(file,s);
        }
        else if(s == "Wizards")
        {
            type = "wiz";
            std::getline(file,s);
        }
        if(type == "sp")
        {
        std::stringstream str(s);
        str>>name_wiz;
        name_book = name_wiz + "'s book";
        Wizards[wiz] = new Wizard(name_wiz, 1, 100, 20, 0, 0, new Book(name_book, 19, new NatureSpell*[0], 0));
        while(str>>d)
        {   
            Wizards[wiz]->book->Nature_spells[num_sp] = createNSp(d);
            Wizards[wiz]->book->Nat_Sp++;
            num_sp++;
        }
        wiz ++;
        num_sp = 0;
        }
        s = "";
    }
    for(int i = 0; i < wiz; i ++)
    {
        Wizards[i]->inf();
    }

}