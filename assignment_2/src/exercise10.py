# use python 3
import sys

if sys.version_info[0] < 3:
    raise Exception("Python 3 changed how generators work so version 2 is not supported")

def ancii_to_byte(e):
    return ord(e)
def byte_to_ancii(e):
    return chr(e)
def str_to_bytes(arr):
    return [ancii_to_byte(e) for e in arr]

def pseudo_random_generation_algorithm(S):
    i = 0; j = 0
    while True:
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]  # python swap without tmp

        K = S[(S[i] + S[j]) % 256]
        yield K

# https://en.wikipedia.org/wiki/RC4
def RC4(text_str, key_str):
    key = str_to_bytes(key_str)
    # Init
    S = [0]*256
    for i in range(256):
        S[i] = i

    # key_scheduling_algorithm
    j = 0
    for i in range(256):
        j = (j + S[i] + key[i % len(key)]) % 256
        S[i], S[j] = S[j], S[i]  # python swap without tmp

    keystream = pseudo_random_generation_algorithm(S)
    # For as many iterations as are needed, the PRGA profides a byte of the keystream

    for i in range(256): # TODO I have no idea how the ignoring works
        keystream.__next__()

    for b in text_str:
        yield ancii_to_byte(b) ^ keystream.__next__() # __next()__  is a python3 thing

# https://en.wikipedia.org/wiki/RC4#Test_vectors
input_key = "key"
input_text = "Plaintext"
output_keystream = "EB9F7781B734CA72A719..."
output_ciphertext = "BBF316E8D940AF0AD3"

for c in RC4(input_text, input_key):
    print(hex(c))