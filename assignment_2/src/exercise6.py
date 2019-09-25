length = 10

super_knapsack = [2]

while (len(super_knapsack) <= length):
    super_knapsack.append(sum(super_knapsack) + 1) # todo random +

s = 120 # todo random

w = [0]*length
for i in range(0, length):
    if s - super_knapsack[length - i] > 0:
        s -= super_knapsack[length - i]
        w[length - i] = 1

print(w, s)
print(super_knapsack)