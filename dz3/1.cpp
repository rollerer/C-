# include <iostream>
# define DYNAMIC_MEMORY 0
#define N 10

void full(int *inp)
{
    for(int i = 0; i<N; i++)
    {
        inp[i] = i*i;
        std::cout<<inp[i]<<'\n';
    }
}
void full(double *inp)
{
    for(int i = 0; i<N; i++)
    {
        inp[i] = i*i;
        std::cout<<inp[i]<<'\n';
    }
}
void full_1(double *inp)
{
    for(int i = 0; i<N; i++)
    {
        inp[i] = (double)i*i/2;
        std::cout<<inp[i]<<'\n';
    }
}

main()
{
#if DYNAMIC_MEMORY == 1
    int *numbers {new int[N]};
    full(numbers);
    delete [] numbers;
#else 
    double massiv[N];
    double *mas = massiv;
    full(mas);
    full_1(mas);
#endif

}

