import collections

def int_to_binary_array(a):
    return bin(a)[2:]


P = collections.namedtuple("P", ['x', 'y'])

a = 20; b = -21

p = 41

P1 = P(3, 6)
N = "?"

alice_m = 44
bob_m = 57

shared_secret = P(P1.x * alice_m * bob_m,  P1.y * alice_m * bob_m)

# Alice and Bob will use the X-coordinate of the shared_secret
print("X-coordinate: ", shared_secret.x)
# Only this key is based on 2 secrets and 1 commen known.
#  - P1 is something they both know
#  - Bob_m is the secred of bob
#  - Alice_m is the secred of alice


# What point is sent by Alice to Bob and what point is sent by Bob to Alice?
alices_message_for_bob = P(P1.x * alice_m,  P1.y * alice_m)
bobs_message_for_alice = P(P1.x * bob_m,    P1.y * bob_m)


# Binary addition
m = 57
binary_m = int_to_binary_array(m)
print(m, "=", binary_m)

additions = 0
if (m != 0):
    additions = -1
    for bit in binary_m:
        if bit == "1":
            additions += 1


print("\nCalculating the numbers: ", len(binary_m), "\tAdding the numbers", additions)
print(len(binary_m) + additions, "additions instead of", m)
print("\nP1 contains 2 numbers so we need to do it 2 times so ", 2 * (len(binary_m) + additions), " additions instead of", 2*m)

"""
P0 = 3        (2^0)   3                 P0 = 6        (2^0)   6    
P0 + P0 = P1  (2^1)   6                 P0 + P0 = P1  (2^1)   12
P1 + P1 = P2  (2^2)   12                P1 + P1 = P2  (2^2)   24
P2 + P2 = P3  (2^3)   24                P2 + P2 = P3  (2^3)   48
P3 + P3 = P4  (2^4)   48                P3 + P3 = P4  (2^4)   96
P4 + P4 = P5  (2^5)   96                P4 + P4 = P5  (2^5)   192

57 = 0b0111001 

57 * P0 = ((P5 + P4) + P3) + P0         57 * P0 = ((P5 + P4) + P3) + P0
57 * 3  = ((96 + 48) + 24) + 3          57 * 6  = ((192+ 96) + 96) + 6

9 additions for 57 * 3                  9 additions for 57 * 6

18 additions in total

"""