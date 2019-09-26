
from hashlib import sha256
import sys

# testing sha256:
password = "Harmony"

sum1 = sha256(str.encode(password)).hexdigest()
# assert sum1 == "184b4d16 bbe3200c 5a5f500cc09efa68cddd42cbda27c1e49fa7a0f2e2735007"                                                     .replace(' ', '')

sum2 = sha256(str.encode(sum1)).hexdigest()
# assert sum2 == "bd11fd28eabd0b87f2ff4595a50041bfb882bbf8ae058ea5d677c7da07d43786"


input_str = input("geef input jonge")
print(input_str)

assert len(input_str) % 8 == 0
# end tests



round = 0
def f(key):
    return key[round*8:round*8+4]

def F(RH, key):
    return f(key)

# str_block is a block of 8 chars.
def feistel(LH, RH, key):
    
    oldLH = LH
    # the old right half becomes the new left half
    LH = RH

    # LH1 ^ F(RH, key)
    # old left half XORed with
    RH = int(oldLH, base = 16) ^ int(F(RH, key), base = 16)

    return (LH, RH)
    

output = ""

for i in range(0, len(input_str), 8):

    str_block = input_str[i:i+8]

    LH = str_block[0:4]
    RH = str_block[4:8]

    key = sum1 + sum2

    for i in range(16):
        LH, RH = feistel(LH, RH, key)
    
    print(feistel(LH, RH, key))
    output += feistel(LH, RH, key)

print(output)

    





