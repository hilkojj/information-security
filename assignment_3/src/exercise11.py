def int_to_binary_array(a):
    return bin(a)[2:]

def pow_mod_n(base, power, n, value=1):
    return pow_mod_n_inner(base, int_to_binary_array(power), n, 1)

def pow_mod_n_inner(base, bits_arr, n, value):
    if len(bits_arr) == 0:
        return value % n 
    
    # because python magic we do not have to apply the rule  (a*b) % N  =>  (a%N * b%N) % N
    value = (value ** 2) * (base ** int(bits_arr[0])) % n 
    return pow_mod_n_inner(base, bits_arr[1:], n, value)


assert pow_mod_n(5, 0, 7) == 1
assert pow_mod_n(5, 0, 1) == 0
assert pow_mod_n(3, 13, 7) == 3
assert pow_mod_n(43210, 23456, 99987) == 82900