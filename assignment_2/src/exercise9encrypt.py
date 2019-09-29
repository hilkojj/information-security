import hashlib
import sys
import array

password = "Angela vs. the NSA"
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
# assert len(input_str) % 8 == 0  # we do not have any garanties about the length we need to pad it
input = [] 
for int_v in input_str:  # we convert the byte string to an array of bytes(ints)
    input.append(int_v)

assert hashlib.sha256(input_str).hexdigest() == \
    "341e680120ae200cfa87c026997e6cf3febb919ccefe5ee599f958b30cbb70a8"

# https://www.cryptosys.net/pki/manpki/pki_paddingschemes.html
padding_length = 8 - (len(input_str) % 8) # pad the input Blocks 
for i in range(padding_length): # N padding bytes of value N 
    input.append(padding_length) 
assert len(input) % padding_length == 0

feistel_bytes = feistelify(input)  # run the feistel algorithm
feistel_str = array.array('B', feistel_bytes).tostring()  # byte array -> string

assert hashlib.sha256(feistel_str).hexdigest() == \
    "a1de533ae72b5907cad02b6ff951cdd363c8d7628ca1e4d22480a49488125c7c"

file = open("exercise9_Hilko_and_Timo.txt", "wb") 
file.write(feistel_str) 
file.close()