
import random
import math
import collections

def generate_primes(n): 
    size = n//2
    sieve = [1]*size
    limit = int(n**0.5)
    for i in range(1,limit):
        if sieve[i]:
            val = 2*i+1
            tmp = ((size-1) - i)//val 
            sieve[i+val::val] = [0]*tmp
    return [2] + [i*2+1 for i, v in enumerate(sieve) if v and i>0]

P = collections.namedtuple("P", ['x', 'y'])

a = random.randint(1, 999)

N = random.choice(generate_primes(9999))

m = random.randint(1, 999)

P1 = P(random.randint(1, 9999), random.randint(1, 9999))

b = (P1.y**2 - (P1.x**3 + a * P1.x)) % N

print("a", a)
print("b", b)
print("N", N)
print(P1)

print("m", m) # 132

P2 = P(P1.x * m, P1.y * m)
print(P2)

"""
a 689
b 911
N 3299
P(x=7179, y=9708)
m 132
P(x=947628, y=1281456)
"""