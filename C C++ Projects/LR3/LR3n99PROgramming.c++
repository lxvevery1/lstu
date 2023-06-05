#include <iostream>
#include <stdlib.h>

int factorial(unsigned int k)
{
    if (k==0)
    {
        return 1;
    }
    else
    {
        return k*factorial(k-1);
    }
}

float sum(int n, double v, unsigned int u)
{
    float a = u;
    float b = v;
    float sum = (a*b)/factorial(2);

    for (unsigned int k = 2; k<n+1; k++)
    {
        float a1 = a;
        a = 2*b+a;
        b = 2*a1*a1+b;
        sum += (a*b)/factorial(k+1);
    }
    return sum;
}

int main()
{
    float u,v;
    unsigned int n;
    std::cout << "u = "; 
    std::cin >> u;
    std::cout << "v = "; 
    std::cin >> v;
    std::cout << "n = "; 
    std::cin >> n;
    std::cout << "sum = " << sum(u, v, n);
return 0;
}