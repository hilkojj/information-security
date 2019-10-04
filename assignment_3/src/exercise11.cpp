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
    // int a=43210, b=23456, c=99987;
    int a=0, b=0, c=0; 
    std::cout << "Base: "; std::cin >> a;
    std::cout << "Power: "; std::cin >> b;
    std::cout << "Mod: "; std::cin >> c;
    
    std::cout << "\n\n";
    std::cout << "Iterative: " << power_mod_n_iterative(a, b, c) << std::endl;
    std::cout << "Recursive: " <<   pow_mod_n_recursive(a, b, c) << std::endl;
    std::cout << "Slides: " <<                pow_mod_n(a, b, c) << std::endl;
    // We evaluate the results of the binary version with a recursive and 
    //  interative version that take O(power)
}