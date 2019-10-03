#include <iostream>
#include <cmath>

#define NTH_BIT(n, k) ((n & ( 1 << k )) >> k)

long power_mod_n_iterative(int base, int power, int n)
{
    long b = base;
    for (int i=1; i<power; i++)
        b = (b * base) % n;
    return b % n;
}

long pow_mod_n_recursive(int base, int power, int n)
{
    if(power == 0) return 0;
    if(power == 1) return base;
    return (base * pow_mod_n_recursive(base, power-1, n)) % n;
}

// if (NTH_BIT(power, index) == true) printf("(%ld,%ld) mod %ld * %ld", value, value, n, base);
// else printf("(%ld,%ld) mod %ld", value, value, n);
// std::cout << " = " << value << "\n";

// We only garantie a correct implementation for interger values
long pow_mod_n(long base, long power, long n, long value = 1, long index = 32)
{
    if (index == -1) return value % n; // if we looked at all bits return value, 

    value = (value * value) % n;
    if (NTH_BIT(power, index)) value = (value * base) % n; // if bit is 1, multiply by the base  (%n)
    
    return pow_mod_n(base, power, n, value, --index); // next bit
}


int main(int argc, char *argv[]) 
{
    int a=43210, b=23456, c=99987;
    // int a=3, b=13, c=7;
    std::cout << "Iterative: " << power_mod_n_iterative(a, b, c) << std::endl;
    std::cout << "Recursive: " <<   pow_mod_n_recursive(a, b, c) << std::endl;
    std::cout << "Slides: " <<                pow_mod_n(a, b, c) << std::endl;
}