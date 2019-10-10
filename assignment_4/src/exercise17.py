import hashlib
import math


people_living_on_earth = 18 * (10**9)

print(hashlib.sha256("password".encode()).hexdigest(), "\n")
# 5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8

# 64 chars of each 16 bits = 1024 bits
bits = len(hashlib.sha256("password".encode()).hexdigest()) * 4
print(bits, "\n") # 256

#
every_posibillity = math.factorial(bits)
print(every_posibillity, "\n")

#
v = every_posibillity // people_living_on_earth
print("This is roughly   2 ^", round(math.log2(v)), "\n")
print("As a power of 10 this is   10 ^", round(math.log(v, 2))//3, "\n")
