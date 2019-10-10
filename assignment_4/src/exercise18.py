# SOURCE https://en.wikipedia.org/wiki/Cyclic_redundancy_check
def crc_remainder(input_bitstring, polynomial_bitstring, initial_filler):
    polynomial_bitstring = polynomial_bitstring.lstrip('0')
    initial_padding = initial_filler * (len(polynomial_bitstring) - 1)
    input_padded = list(input_bitstring + initial_padding)

    while '1' in input_padded[:len(input_bitstring)]:
        cur_shift = input_padded.index('1')
        for i in range(len(polynomial_bitstring)):
            input_padded[cur_shift + i] = str(int(polynomial_bitstring[i] != input_padded[cur_shift + i]))
    return ''.join(input_padded)[len(input_bitstring):]


# SOURCE https://en.wikipedia.org/wiki/Cyclic_redundancy_check
def crc_check(input_bitstring, polynomial_bitstring, check_value):
    polynomial_bitstring = polynomial_bitstring.lstrip('0')
    initial_padding = check_value
    input_padded = list(input_bitstring + initial_padding)

    while '1' in input_padded[:len(input_bitstring)]:
        cur_shift = input_padded.index('1')
        for i in range(len(polynomial_bitstring)):
            input_padded[cur_shift + i] = str(int(polynomial_bitstring[i] != input_padded[cur_shift + i]))
    return ('1' not in ''.join(input_padded)[len(input_bitstring):])


print(crc_remainder('10101011','10011','0'))  # 1010


# Opdracht 8
print(crc_check('10101011','10011','1010'))
print(crc_check('00000110','10011','1010'))
print(crc_check('00100000','10011','1010'))

# 00000110
# 00100000



# OPGAVE 9
print("\n\n")
for i in range(0,2**5):
    v = '111'+("{0:b}".format(i).zfill(5))
    if crc_check(v,'10011','1010'):
        print(v)

# 11100111
# 11110100