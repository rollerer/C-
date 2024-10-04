#include <iostream>
# define N 5
 
 
struct vector
{
    float m[N];
    void plur(float a)
    {
        for (int i = 0; i<N;i++)
        {
            m[i]*=a;
        }
    }
    
};

struct vector sum(struct vector a, struct vector b)
    {   
        struct vector c {};
        for(int i = 0; i<N; i++)
        {
            c.m[i] = a.m[i] + b.m[i];
        }
        return c;
    }
float scal(struct vector a, struct vector b)
    {   
        float c;
        for(int i = 0; i<N; i++)
        {
            c  += a.m[i]*b.m[i];
        }
        return c;
    }
 
main()
{   
    std::cout<<"Write "<<N<<" coords of two vectors x_1 y_1; x_2 y_2...";
    struct vector v_1 {};
    struct vector v_2 {};
    for (int i = 0; i<N; i++)
    {
        float x,y;
        std::cin>>x>>y;
        v_1.m[i] = x;
        v_2.m[i] = y;
    }
    struct vector v_3 = sum(v_1, v_2);  
    float s = scal(v_1, v_2);
    std::cout<<v_3.m[1];
}