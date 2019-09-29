import hashlib
import sys

password = "Harmony" # "Feistel" and "Harmony" run aditional assertions
sum1 = hashlib.sha256(password.encode())
sum2 = hashlib.sha256(sum1.hexdigest().encode())

if password == "Feistel":
    assert sum1.hexdigest() == "184b4d16bbe3200c5a5f500cc09efa68cddd42cbda27c1e49fa7a0f2e2735007"
    assert sum2.hexdigest() == "bd11fd28eabd0b87f2ff4595a50041bfb882bbf8ae058ea5d677c7da07d43786"

key = sum1.digest() + sum2.digest()
assert len(key) == 64


def xor(half_block_a, half_block_b):
    new_block = []
    for i in range(4):
        new_block.append((half_block_a[i] ^ half_block_b[i]) % 256)
    return new_block
    
assert xor([1, 1, 2, 2], [1, 2, 1, 2]) == [0, 3, 3, 0]


def f(key, round):
    return key[4*round:(4*round)+4]

def feistel(block_8_byte):
    LH = block_8_byte[0:4]
    RH = block_8_byte[4:8]
    
    for r in range(16):
        oldLH = LH[:]
        LH = RH[:]
        RH = xor(oldLH, f(key, r))

    return LH + RH

def feistelify(input):
    output = []
    for i in range(0, len(input), 8):
        out = feistel(input[i:i+8])
        for x in out:
            output.append(x)
    
    return output

input_str = sys.stdin.buffer.read()
assert len(input_str) % 8 == 0
input = []
for int_v in input_str:
    input.append(int_v)

feistel_bytes = feistelify(input)
for b in feistel_bytes:
    print(chr(b), end="")



if password == "Harmony":
    example_harmony = [84, 104, 101, 32, 83, 121, 109, 112, 104, 111, 110, 121, 32, 111, 102, 32, 82, 101, 97, 108, 105, 116, 121, 32, 116, 104, 101, 32, 72, 97, 114, 109, 111, 110, 121, 32, 111, 102, 32, 67, 104, 97, 111, 115, 46, 32, 84, 104, 101, 32, 72, 97, 114, 109, 111, 110, 121, 32, 111, 102, 32, 67, 104, 97, 111, 115, 32, 105, 115, 32, 116, 104, 101, 32, 83, 121, 109, 112, 104, 111, 110, 121, 32, 111, 102, 32, 67, 111, 108, 111, 114, 115, 46, 120, 120, 10]
    harmony_binary = [118, 173, 207, 231, 169, 99, 239, 143, 74, 170, 196, 190, 218, 117, 228, 223, 112, 160, 203, 171, 147, 110, 251, 223, 86, 173, 207, 231, 178, 123, 240, 146, 77, 171, 211, 231, 149, 124, 162, 188, 74, 164, 197, 180, 212, 58, 214, 151, 71, 229, 226, 166, 136, 119, 237, 145, 91, 229, 197, 161, 218, 89, 234, 158, 77, 182, 138, 174, 137, 58, 246, 151, 71, 229, 249, 190, 151, 106, 234, 144, 76, 188, 138, 168, 156, 58, 193, 144, 78, 170, 216, 180, 212, 98, 250, 245]
    assert len(example_harmony) % 8 == 0 and len(harmony_binary) % 8 == 0

    assert feistelify(example_harmony) == harmony_binary
    assert feistelify(harmony_binary) == example_harmony