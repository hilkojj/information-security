text = "informationsecurity"
key = "vlaksjdhfgqodzmxncb"

def ancii_to_byte(e):
    return ord(e)
def byte_to_ancii(e):
    return chr(e)

def vernam_cipher(text, key):
    cipher = ""
    for i, c in enumerate(text):
        b_byte = ancii_to_byte(c) ^ ancii_to_byte(key[i]) % 256
        cipher += byte_to_ancii(b_byte)

    return cipher

print(vernam_cipher(text, key))
print(vernam_cipher(vernam_cipher(text, key), "tlftrffwmixor|{xbch"))
