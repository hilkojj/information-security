#include <iostream>
#include <cmath>

long power_mod_n_iterative(int base, int power, int n)
{
    long b = base;
    for (int i=1; i<power; i++)
        b = (b * base) % n;
    return b % n;
}

long pow_mod_n(int base, int power, int n)
{
    if(power == 0) return 0;
    if(power == 1) return base;
    return (base * pow_mod_n(base, power-1, n)) % n;
}

int main(int argc, char *argv[]) 
{
    int a=43210, b=7, c=99987;
    std::cout << power_mod_n_iterative(a, b, c) << std::endl;
    std::cout <<             pow_mod_n(a, b, c) << std::endl;
}