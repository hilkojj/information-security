
#include <iostream>
#include <set>
#include <math.h>
#include <vector>

std::set<int> primeFactorSet(int v)
{
    std::set<int> factorSet;
    int i = 1;
    while (v > 1)
    {
        i++;
        while (v % i == 0)
        {
            factorSet.insert(i);
            v /= i;
        }
    }
    return factorSet;
}

long pow_mod_n(int base, int power, int n)
{
    if(power == 0) return 0;
    if(power == 1) return base;
    return (base * pow_mod_n(base, power-1, n)) % n;
}

std::vector<int> generator(int p)
{
    bool potentionalG[p-1] = {0};
    for (int x : primeFactorSet(p - 1))
        for (int g = 2; g < p - 1; g++)
            if (pow_mod_n(g, (p-1)/x, p) == 1)
                potentionalG[g] = 1;

    std::vector<int> indices;
    int i = 0;
    for (bool pG : potentionalG)
    {
        if (!pG) {
            std::cout << '1';
            indices.push_back(i);
        } else std::cout << '0';
        i++;
    }
    std::cout << '\n';
    return indices;
}

// 1100010111111111111111
int main()
{
// 
    // for (int x : primeFactorSet(7919 - 1)) std::cout << x << "\n";

    std::cout << generator(23)[2] << "\n";


    return 0;
}
