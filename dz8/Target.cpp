#include <iostream>
#include <math.h>	

#ifndef M
#define M
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
        int coord[2] = {0, 0};
        int FreeDebuff = 0;
        int FreeBuff = 0;
        virtual void inf() = 0;
        
};

float dist(Target* a, Target*b)
{   
    double n = pow(a->coord[0] - b->coord[0], 2);
    double m = pow(a->coord[1] - b->coord[1], 2);
    return pow(n+m, 0.5);
}

void move(Target* a, Target* b)
{
    if (abs(a->coord[0] - b->coord[0]) > abs(a->coord[1] - b->coord[1]))
    {
        if(a->coord[0] > b->coord[0])
        {
            a->coord[0] -= 1;
        }
        else
        {
            a->coord[0] += 1;
        }
    }
    else
    {
        if(a->coord[1] > b->coord[1])
        {
            a->coord[1] -= 1;
        }
        else
        {
            a->coord[1] += 1;
        }
    }
}
#endif
