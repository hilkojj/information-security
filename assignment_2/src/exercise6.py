
"""
26 170277
[52, 104, 286, 546, 1092, 2158, 4342, 8632, 17316, 34580, 69160, 138372, 106441, 42579, 85132, 13]
[2, 4, 11, 21, 42, 83, 167, 332, 666, 1330, 2660, 5322, 10643, 21285, 42569, 85139] 111335
"""

import random
import math

def get_super_increasing_ks(length):
    #todo
    # return [2, 3, 7, 14, 30, 57, 120, 251]

    ks = [0] * length
    for i in range(length):
        ks[i] = sum(ks) + random.randint(1, 5)
    return ks

def is_rp(x, y):
    return math.gcd(x, y) == 1

def m_and_n_for_super_ks(superks):
    # return [41, 491]
    while True:
        m = random.randint(10, 999)
        while True:

            n = sum(superks) + 1

            if m > n:
                break

            while True:
                
                if is_rp(m, n):
                    return (m, n)

                n += 1

            m += 1


def get_general_ks(m, n, superks):
    return [(s * m) % n for s in superks]

def modular_inverse(a, m):
    # ax === 1 (mod m)
    x = 0
    while True:
        if (a * x) % m == 1:
            return x
        x += 1

superiks = get_super_increasing_ks(16)
m, n = m_and_n_for_super_ks(superiks)

public_key = get_general_ks(m, n, superiks)
private_key = modular_inverse(m, n)

print(m, n)
print(public_key)
print(superiks, private_key)


