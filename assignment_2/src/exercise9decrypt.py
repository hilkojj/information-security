import hashlib
import sys
import array

password = "The Feistel Cipher"
sum1 = hashlib.sha256(password.encode())
sum2 = hashlib.sha256(sum1.hexdigest().encode())

key = sum1.digest() + sum2.digest()
assert len(key) == 64


def xor(half_block_a, half_block_b):  # xor on 2 half blocks
    new_block = []
    for i in range(4):
        new_block.append((half_block_a[i] ^ half_block_b[i]) % 256)
    return new_block
    
assert xor([1, 1, 2, 2], [1, 2, 1, 2]) == [0, 3, 3, 0]


def f(key, round):
    return key[4*round:(4*round)+4]

def feistel(block_8_byte):  # feistel algoritm for a block(array) of 8 bytes(int)
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
# assert len(input_str) % 8 == 0  # no ganranties about the length so padding is added
input = [] 
for int_v in input_str:  # we convert the byte string to an array of bytes(ints)
    input.append(int_v)


feistel_bytes = feistelify(input)  # run the feistel algorithm
feistel_str = array.array('B', feistel_bytes).tostring()  # byte array -> string

padding_length = feistel_bytes[-1] # the last digit contains the amount of padding bytes
output = feistel_str[:-padding_length] # slice the padding away
for b in output: # print
    print(chr(b), end="")
