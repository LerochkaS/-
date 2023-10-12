import random
import math

def rhoFactorization(m: int, maxstep = 10000000) -> int:
    x: int = random.randint(2, m-1)
    y: int = x*x + 1 % m
    d: int = math.gcd(x-y, m)
    steps: int = 0
    while d == 1 & d != m & steps < maxstep:
        x = x*x + 1 % m
        y = y*y +1 % m
        y = y*y + 1 % m
        d = math.gcd(x-y, m)
        steps += 1
    if d == m:
        d = 1
    return d

#print("Введите целое число для разложения: ")
m: int = int(input("Введите целое число для разложения: "))
d: int = rhoFactorization(m)
if d == 1:
    print("FAIL!")
else:
    print(f"Нетривиальный делитель числа {m} : {d}")